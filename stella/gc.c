#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "runtime.h"
#include "gc.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

/** Total allocated number of bytes (over the entire duration of the program). */
int total_allocated_bytes = 0;

/** Total allocated number of objects (over the entire duration of the program). */
int total_allocated_objects = 0;

int max_allocated_bytes = 0;
int max_allocated_objects = 0;

int total_reads = 0;
int total_writes = 0;

#define MAX_GC_ROOTS 1024

int gc_roots_max_size = 0;
int gc_roots_top = 0;
void **gc_roots[MAX_GC_ROOTS];

#ifndef MAX_ALLOC_SIZE
#define MAX_ALLOC_SIZE (2 * 1024 * 1024)
#endif  // MAX_ALLOC_SIZE

// 4 * MAX_ALLOC_SIZE to avoid wild pointer comparisons which are UB by C ISO
static char memory[4 * MAX_ALLOC_SIZE] __attribute__ ((aligned (sizeof(void*))));

static char *from_space = memory + MAX_ALLOC_SIZE;
static char *to_space = memory + 2 * MAX_ALLOC_SIZE;
static char *scan = memory + 2 * MAX_ALLOC_SIZE;
static char *next = memory + 2 * MAX_ALLOC_SIZE;
static char *limit = memory + 3 * MAX_ALLOC_SIZE;

static void gc_out_of_memory_perror(const char* context) {
  fprintf(stderr, "\n=======================================================\n");
  fprintf(stderr, "!!!FAILURE!!!\n");
  fprintf(stderr, "\tOUT OF MEMORY: %s\n", context);
  fprintf(stderr, "=======================================================\n");

  exit(1);
}

static int gc_object_space_test(void *object, void *space) {
  return (0 < ((char*)object - (char*)space) && ((char*)object - (char*)space) < MAX_ALLOC_SIZE);
}

static void gc_chase(void *object) {
  stella_object* sobject = object;

  while (sobject) {
    stella_object *fwd = (stella_object*)next;
    if (limit < next + sizeof(void*) * (STELLA_OBJECT_HEADER_FIELD_COUNT(sobject->object_header) + 1)) {
      gc_out_of_memory_perror("chasing pointers next pointer overflow");
    }
    memcpy(fwd, sobject, sizeof(void*) * (STELLA_OBJECT_HEADER_FIELD_COUNT(sobject->object_header) + 1));
    next = next + sizeof(void*) * (STELLA_OBJECT_HEADER_FIELD_COUNT(sobject->object_header) + 1);

    stella_object *candidate = NULL;
    for (size_t i = 0; i < STELLA_OBJECT_HEADER_FIELD_COUNT(sobject->object_header); i++) {
      if (!gc_object_space_test((stella_object*) fwd->object_fields[i], from_space) ||
          gc_object_space_test(((stella_object*) fwd->object_fields[i])->object_fields[0], to_space)) {
        continue;
      }

      candidate = fwd->object_fields[i];
      break;
    }


    sobject->object_fields[0] = fwd;
    sobject = candidate;
  }
}

static void* gc_forward(void *object) {
  if (!object) {
    return object;
  }

  if (gc_object_space_test((stella_object*) object, from_space)) {
    if (!gc_object_space_test(((stella_object*) object)->object_fields[0], to_space)) {
      gc_chase(object);
    }

    return ((stella_object*) object)->object_fields[0];
  }

  return object;
}

static void gc_deep_copy(stella_object* object) {
  for (int i = 0; i < STELLA_OBJECT_HEADER_FIELD_COUNT(object->object_header); i++) {
    object->object_fields[i] = gc_forward(object->object_fields[i]);
  }
}

static void gc_swap_spaces(void) {
  char *temp = from_space;
  from_space = to_space;
  to_space = temp;

  scan = to_space;
  next = to_space;
  limit = to_space + MAX_ALLOC_SIZE;
}

static void gc_flip(void) {
  gc_swap_spaces();

  for (int i = 0; i < gc_roots_top; i++) {
    *gc_roots[i] = gc_forward(*gc_roots[i]);
  }
}

void* gc_alloc(size_t size_in_bytes) {
  size_in_bytes = ((size_in_bytes + sizeof(void*) - 1) / sizeof(void*)) * sizeof(void*);

  if (scan != next) {
    gc_deep_copy((stella_object*)scan);
    scan = scan + sizeof(void*) * (STELLA_OBJECT_HEADER_FIELD_COUNT(((stella_object*)scan)->object_header) + 1);
  }

  if (limit < next + size_in_bytes) {
    while (0 < next - scan) {
      gc_deep_copy((stella_object*)scan);
      scan = scan + sizeof(void*) * (STELLA_OBJECT_HEADER_FIELD_COUNT(((stella_object*)scan)->object_header) + 1);
    }

    gc_flip();
    if (limit < next + size_in_bytes) {
      gc_out_of_memory_perror("not enough memory to alloc, even after gc_flip");
    }
  }

  total_allocated_bytes += size_in_bytes;
  max_allocated_bytes = MAX(total_allocated_bytes, max_allocated_bytes);

  total_allocated_objects++;
  max_allocated_objects = MAX(total_allocated_objects, max_allocated_objects);

  limit = limit - size_in_bytes;
  memset(limit, 0, size_in_bytes);
  return limit;
}

void print_gc_roots(void) {
  printf("ROOTS: ");
  for (int i = 0; i < gc_roots_top; i++) {
    printf("%p ", gc_roots[i]);
  }
  printf("\n");
}

void print_gc_alloc_stats(void) {
  printf("Total memory allocation: %'d bytes (%'d objects)\n", total_allocated_bytes, total_allocated_objects);
  printf("Maximum residency:       %'d bytes (%'d objects)\n", max_allocated_bytes, max_allocated_objects);
  printf("Total memory use:        %'d reads and %'d writes\n", total_reads, total_writes);
  printf("Max GC roots stack size: %'d roots\n", gc_roots_max_size);
}

static void stella_print_object(stella_object *object) {
  printf("\tObject with %d fields at %p of kind %d:\n\t", 
    STELLA_OBJECT_HEADER_FIELD_COUNT(object->object_header), 
    object, 
    STELLA_OBJECT_HEADER_TAG(object->object_header));
  print_stella_object(object);
  printf("\n");

  for (int i = 0; i < STELLA_OBJECT_HEADER_FIELD_COUNT(object->object_header); i++) {
    if (object == &the_ZERO) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "ZERO", 
           object->object_fields[i]);
    } else if (object == &the_UNIT) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "UNIT", 
           object->object_fields[i]);
    } else if (object == &the_EMPTY) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "EMPTY", 
           object->object_fields[i]);
    } else if (object == &the_EMPTY_TUPLE) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "TUPLE", 
           object->object_fields[i]);
    } else if (object == &the_FALSE) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "FALSE", 
           object->object_fields[i]);
    } else if (object == &the_TRUE) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "TRUE", 
           object->object_fields[i]);
    } else if (gc_object_space_test(object, to_space)) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "to-space", 
           object->object_fields[i]);
    } else if (gc_object_space_test(object, from_space)) {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "from-space", 
           object->object_fields[i]);
    } else {
      printf("\t\tField #%d at %p is a \"%s\" at %p\n",
           i + 1, 
           (char*)object + (i + 1) * sizeof(void*), 
           "nil", 
           object->object_fields[i]);
    }
  }
}

static void print_to_space_state(void) {
  char* iterator = to_space;

  while (0 < next - iterator) {
    stella_print_object((stella_object*)iterator);
    iterator = (char*)iterator + sizeof(void*) * (1 + STELLA_OBJECT_HEADER_FIELD_COUNT(((stella_object*)iterator)->object_header));
  }
  while (0 < limit - iterator) {
    printf("\tNone: %p\n", iterator);
    iterator = (char*)iterator + sizeof(void*);
  }
  while (iterator - to_space < MAX_ALLOC_SIZE) {
    stella_print_object((stella_object*)iterator);
    iterator = (char*)iterator + sizeof(void*) * (1 + STELLA_OBJECT_HEADER_FIELD_COUNT(((stella_object*)iterator)->object_header));
  }

}

void print_gc_state(void) {
  printf("\n======================== GC State ========================\n");

  print_gc_roots();

  printf("==========================================================\n");
  
  printf("Pointer values:\n");
  printf("\tFrom-space pointer:\t%p\n", from_space);  
  printf("\tTo-space pointer:\t%p\n", to_space);
  printf("\t\"Next\" pointer:\t%p\n", next);
  printf("\t\"Limit\" pointer:\t%p", limit);
  printf("\t\"Scan\" pointer:\t%p\n", scan);

  printf("==========================================================\n");

  printf("To-space:\n");
  print_to_space_state();

  printf("==========================================================\n\n");
}

void gc_read_barrier(void *object, int field_index) {
  total_reads++;

  gc_forward(((stella_object*)object)->object_fields[field_index]);
}

void gc_write_barrier(void *object, int field_index, void *contents) {
  total_writes++;
}

void gc_push_root(void **ptr) {
  if (gc_roots_top > MAX_GC_ROOTS) {
    gc_out_of_memory_perror("too much roots");
  }

  gc_roots[gc_roots_top++] = ptr;
  gc_roots_max_size = MAX(gc_roots_top, gc_roots_max_size); 
}

void gc_pop_root(void **ptr) {
  gc_roots_top--;
}
