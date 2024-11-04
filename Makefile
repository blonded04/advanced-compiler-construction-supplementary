examples: example_factorial.out example_logical_operations.out example_square_numbers.out

install:
	docker image pull fizruk/stella:latest

example_factorial.out: runtime.o gc.o examples/factorial.stella
	docker run -i fizruk/stella compile < examples/factorial.stella > TEMPORARY_factorial.c
	gcc -O0 -std=c11 -g3 -fsanitize=address runtime.o gc.o TEMPORARY_factorial.c -I. -o example_factorial.out

example_logical_operations.out: runtime.o gc.o examples/logical_operations.stella
	docker run -i fizruk/stella compile < examples/logical_operations.stella > TEMPORARY_logical_operations.c
	gcc -O0 -std=c11 -g3 -fsanitize=address runtime.o gc.o TEMPORARY_logical_operations.c -I. -o example_logical_operations.out

example_square_numbers.out: runtime.o gc.o examples/square_numbers.stella
	docker run -i fizruk/stella compile < examples/square_numbers.stella > TEMPORARY_square_numbers.c
	gcc -O0 -std=c11 -g3 -fsanitize=address runtime.o gc.o TEMPORARY_square_numbers.c -I. -o example_square_numbers.out

gc.o: stella/gc.h stella/gc.c
	gcc -O0 -std=c11 -g3 -fsanitize=address -Werror -c stella/gc.c

runtime.o: stella/runtime.h stella/runtime.c stella/gc.h
	gcc -O0 -std=c11 -g3 -fsanitize=address -Werror -c stella/runtime.c

all: install examples

clean:
	rm -f *.out *.o TEMPORARY_*

.PHONY: install all clean
