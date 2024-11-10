# Advanced compiler construction course (HSE SPb, Fall 2024) supplementary repository

[Incremental garbage collector](https://github.com/blonded04/advanced-compiler-construction-supplementary/tree/t01-garbage-collector) (based on [Baker's algorithm](https://dl.acm.org/doi/pdf/10.1145/130854.130862)) for [Stella language](https://fizruk.github.io/stella/) runtime 

## Build

Just do:
```
make all
```

It produces binaries of examples and also lives you with `gc.o` and `runtime.o` files which you can use to compile your own examples with.

## `print_gc_alloc_stats` and `print_gc_state` format 

GC state:

```
======================== GC State ========================
ROOTS: 0x7ffc6ee57790 0x7ffc6ee577b0 0x7ffc6ee577d0 0x7ffc6ee57670 0x7ffc6ee57690 0x7ffc6ee576b0 0x7ffc6ee576d0 0x7ffc6ee576f0 0x7ffc6ee57590 0x7ffc6ee575b0 0x7ffc6ee575d0 0x7ffc6ee57410 0x7ffc6ee57430 0x7ffc6ee57450 0x7ffc6ee57470 0x7ffc6ee57490 0x7ffc6ee574b0 0x7ffc6ee574d0 0x7ffc6ee573f0 0x7ffc6ee572d0 0x7ffc6ee572f0 0x7ffc6ee57310 0x7ffc6ee57330 0x7ffc6ee57350 0x7ffc6ee572b0 0x7ffc6ee571d0 0x7ffc6ee571f0 
==========================================================
Pointer values:
	From-space pointer:	0x559bf04b8a60
	To-space pointer:	0x559bf04b9260
	"Next" pointer:	0x559bf04b9260
	"Limit" pointer:	0x559bf04b96b0	"Scan" pointer:	0x559bf04b9260
==========================================================
To-space:
	None: 0x559bf04b9260
	None: 0x559bf04b9268
	None: 0x559bf04b9270
	None: 0x559bf04b9278
	None: 0x559bf04b9280
	None: 0x559bf04b9288
	None: 0x559bf04b9290
	None: 0x559bf04b9298
	None: 0x559bf04b92a0
	None: 0x559bf04b92a8
	None: 0x559bf04b92b0
	None: 0x559bf04b92b8
	None: 0x559bf04b92c0
	None: 0x559bf04b92c8
	None: 0x559bf04b92d0
	None: 0x559bf04b92d8
	None: 0x559bf04b92e0
	None: 0x559bf04b92e8
	None: 0x559bf04b92f0
	None: 0x559bf04b92f8
	None: 0x559bf04b9300
	None: 0x559bf04b9308
	None: 0x559bf04b9310
	None: 0x559bf04b9318
	None: 0x559bf04b9320
	None: 0x559bf04b9328
	None: 0x559bf04b9330
	None: 0x559bf04b9338
	None: 0x559bf04b9340
	None: 0x559bf04b9348
	None: 0x559bf04b9350
	None: 0x559bf04b9358
	None: 0x559bf04b9360
	None: 0x559bf04b9368
	None: 0x559bf04b9370
	None: 0x559bf04b9378
	None: 0x559bf04b9380
	None: 0x559bf04b9388
	None: 0x559bf04b9390
	None: 0x559bf04b9398
	None: 0x559bf04b93a0
	None: 0x559bf04b93a8
	None: 0x559bf04b93b0
	None: 0x559bf04b93b8
	None: 0x559bf04b93c0
	None: 0x559bf04b93c8
	None: 0x559bf04b93d0
	None: 0x559bf04b93d8
	None: 0x559bf04b93e0
	None: 0x559bf04b93e8
	None: 0x559bf04b93f0
	None: 0x559bf04b93f8
	None: 0x559bf04b9400
	None: 0x559bf04b9408
	None: 0x559bf04b9410
	None: 0x559bf04b9418
	None: 0x559bf04b9420
	None: 0x559bf04b9428
	None: 0x559bf04b9430
	None: 0x559bf04b9438
	None: 0x559bf04b9440
	None: 0x559bf04b9448
	None: 0x559bf04b9450
	None: 0x559bf04b9458
	None: 0x559bf04b9460
	None: 0x559bf04b9468
	None: 0x559bf04b9470
	None: 0x559bf04b9478
	None: 0x559bf04b9480
	None: 0x559bf04b9488
	None: 0x559bf04b9490
	None: 0x559bf04b9498
	None: 0x559bf04b94a0
	None: 0x559bf04b94a8
	None: 0x559bf04b94b0
	None: 0x559bf04b94b8
	None: 0x559bf04b94c0
	None: 0x559bf04b94c8
	None: 0x559bf04b94d0
	None: 0x559bf04b94d8
	None: 0x559bf04b94e0
	None: 0x559bf04b94e8
	None: 0x559bf04b94f0
	None: 0x559bf04b94f8
	None: 0x559bf04b9500
	None: 0x559bf04b9508
	None: 0x559bf04b9510
	None: 0x559bf04b9518
	None: 0x559bf04b9520
	None: 0x559bf04b9528
	None: 0x559bf04b9530
	None: 0x559bf04b9538
	None: 0x559bf04b9540
	None: 0x559bf04b9548
	None: 0x559bf04b9550
	None: 0x559bf04b9558
	None: 0x559bf04b9560
	None: 0x559bf04b9568
	None: 0x559bf04b9570
	None: 0x559bf04b9578
	None: 0x559bf04b9580
	None: 0x559bf04b9588
	None: 0x559bf04b9590
	None: 0x559bf04b9598
	None: 0x559bf04b95a0
	None: 0x559bf04b95a8
	None: 0x559bf04b95b0
	None: 0x559bf04b95b8
	None: 0x559bf04b95c0
	None: 0x559bf04b95c8
	None: 0x559bf04b95d0
	None: 0x559bf04b95d8
	None: 0x559bf04b95e0
	None: 0x559bf04b95e8
	None: 0x559bf04b95f0
	None: 0x559bf04b95f8
	None: 0x559bf04b9600
	None: 0x559bf04b9608
	None: 0x559bf04b9610
	None: 0x559bf04b9618
	None: 0x559bf04b9620
	None: 0x559bf04b9628
	None: 0x559bf04b9630
	None: 0x559bf04b9638
	None: 0x559bf04b9640
	None: 0x559bf04b9648
	None: 0x559bf04b9650
	None: 0x559bf04b9658
	None: 0x559bf04b9660
	None: 0x559bf04b9668
	None: 0x559bf04b9670
	None: 0x559bf04b9678
	None: 0x559bf04b9680
	None: 0x559bf04b9688
	None: 0x559bf04b9690
	None: 0x559bf04b9698
	None: 0x559bf04b96a0
	None: 0x559bf04b96a8
	Object with 1 fields at 0x559bf04b96b0 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b96b8 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b96c0 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b96c8 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b96d0 of kind 1:
	16
		Field #1 at 0x559bf04b96d8 is a "to-space" at 0x559bf04b9728
	Object with 2 fields at 0x559bf04b96e0 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b96e8 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b96f0 is a "to-space" at 0x559bf04b5fe0
	Object with 2 fields at 0x559bf04b96f8 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b9700 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b9708 is a "to-space" at 0x559bf04b5fe0
	Object with 2 fields at 0x559bf04b9710 of kind 4:
	fn<0x559bf04ae209>
		Field #1 at 0x559bf04b9718 is a "to-space" at 0x559bf04ae209
		Field #2 at 0x559bf04b9720 is a "to-space" at 0x559bf04b5fe0
	Object with 1 fields at 0x559bf04b9728 of kind 1:
	15
		Field #1 at 0x559bf04b9730 is a "to-space" at 0x559bf04b9758
	Object with 1 fields at 0x559bf04b9738 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9740 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9748 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b9750 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b9758 of kind 1:
	14
		Field #1 at 0x559bf04b9760 is a "to-space" at 0x559bf04b9788
	Object with 1 fields at 0x559bf04b9768 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9770 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9778 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b9780 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b9788 of kind 1:
	13
		Field #1 at 0x559bf04b9790 is a "to-space" at 0x559bf04b97e0
	Object with 2 fields at 0x559bf04b9798 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b97a0 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b97a8 is a "to-space" at 0x559bf04b9a50
	Object with 2 fields at 0x559bf04b97b0 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b97b8 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b97c0 is a "to-space" at 0x559bf04b9a50
	Object with 2 fields at 0x559bf04b97c8 of kind 4:
	fn<0x559bf04ae209>
		Field #1 at 0x559bf04b97d0 is a "to-space" at 0x559bf04ae209
		Field #2 at 0x559bf04b97d8 is a "to-space" at 0x559bf04b9a50
	Object with 1 fields at 0x559bf04b97e0 of kind 1:
	12
		Field #1 at 0x559bf04b97e8 is a "to-space" at 0x559bf04b9800
	Object with 1 fields at 0x559bf04b97f0 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b97f8 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9800 of kind 1:
	11
		Field #1 at 0x559bf04b9808 is a "to-space" at 0x559bf04b9830
	Object with 1 fields at 0x559bf04b9810 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9818 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9820 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b9828 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b9830 of kind 1:
	10
		Field #1 at 0x559bf04b9838 is a "to-space" at 0x559bf04b9850
	Object with 1 fields at 0x559bf04b9840 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9848 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9850 of kind 1:
	9
		Field #1 at 0x559bf04b9858 is a "to-space" at 0x559bf04b9880
	Object with 1 fields at 0x559bf04b9860 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9868 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9870 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b9878 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b9880 of kind 1:
	8
		Field #1 at 0x559bf04b9888 is a "to-space" at 0x559bf04b98d8
	Object with 2 fields at 0x559bf04b9890 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b9898 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b98a0 is a "to-space" at 0x559bf04b9a40
	Object with 2 fields at 0x559bf04b98a8 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b98b0 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b98b8 is a "to-space" at 0x559bf04b9a40
	Object with 2 fields at 0x559bf04b98c0 of kind 4:
	fn<0x559bf04ae209>
		Field #1 at 0x559bf04b98c8 is a "to-space" at 0x559bf04ae209
		Field #2 at 0x559bf04b98d0 is a "to-space" at 0x559bf04b9a40
	Object with 1 fields at 0x559bf04b98d8 of kind 1:
	7
		Field #1 at 0x559bf04b98e0 is a "to-space" at 0x559bf04b98f8
	Object with 1 fields at 0x559bf04b98e8 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b98f0 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b98f8 of kind 1:
	6
		Field #1 at 0x559bf04b9900 is a "to-space" at 0x559bf04b9918
	Object with 1 fields at 0x559bf04b9908 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9910 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9918 of kind 1:
	5
		Field #1 at 0x559bf04b9920 is a "to-space" at 0x559bf04b9948
	Object with 1 fields at 0x559bf04b9928 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9930 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9938 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b9940 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b9948 of kind 1:
	4
		Field #1 at 0x559bf04b9950 is a "to-space" at 0x559bf04b9968
	Object with 1 fields at 0x559bf04b9958 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9960 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9968 of kind 1:
	3
		Field #1 at 0x559bf04b9970 is a "to-space" at 0x559bf04b9988
	Object with 1 fields at 0x559bf04b9978 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b9980 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b9988 of kind 1:
	2
		Field #1 at 0x559bf04b9990 is a "to-space" at 0x559bf04b99b8
	Object with 1 fields at 0x559bf04b9998 of kind 4:
	fn<0x559bf04ad80a>
		Field #1 at 0x559bf04b99a0 is a "to-space" at 0x559bf04ad80a
	Object with 1 fields at 0x559bf04b99a8 of kind 4:
	fn<0x559bf04adab7>
		Field #1 at 0x559bf04b99b0 is a "to-space" at 0x559bf04adab7
	Object with 1 fields at 0x559bf04b99b8 of kind 1:
	1
		Field #1 at 0x559bf04b99c0 is a "to-space" at 0x559bf04b5fe0
	Object with 2 fields at 0x559bf04b99c8 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b99d0 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b99d8 is a "to-space" at 0x559bf04b9a30
	Object with 2 fields at 0x559bf04b99e0 of kind 4:
	fn<0x559bf04adcf3>
		Field #1 at 0x559bf04b99e8 is a "to-space" at 0x559bf04adcf3
		Field #2 at 0x559bf04b99f0 is a "to-space" at 0x559bf04b9a30
	Object with 2 fields at 0x559bf04b99f8 of kind 4:
	fn<0x559bf04ae209>
		Field #1 at 0x559bf04b9a00 is a "to-space" at 0x559bf04ae209
		Field #2 at 0x559bf04b9a08 is a "to-space" at 0x559bf04b9a30
	Object with 1 fields at 0x559bf04b9a10 of kind 4:
	fn<0x559bf04aeb1f>
		Field #1 at 0x559bf04b9a18 is a "to-space" at 0x559bf04aeb1f
	Object with 1 fields at 0x559bf04b9a20 of kind 1:
	4
		Field #1 at 0x559bf04b9a28 is a "to-space" at 0x559bf04b9a30
	Object with 1 fields at 0x559bf04b9a30 of kind 1:
	3
		Field #1 at 0x559bf04b9a38 is a "to-space" at 0x559bf04b9a40
	Object with 1 fields at 0x559bf04b9a40 of kind 1:
	2
		Field #1 at 0x559bf04b9a48 is a "to-space" at 0x559bf04b9a50
	Object with 1 fields at 0x559bf04b9a50 of kind 1:
	1
		Field #1 at 0x559bf04b9a58 is a "to-space" at 0x559bf04b5fe0
==========================================================
```

GC Statisitics:
```
------------------------------------------------------------
Garbage collector (GC) statistics:
Total memory allocation: 944 bytes (53 objects)
Maximum residency:       944 bytes (53 objects)
Total memory use:        16 287 reads and 0 writes
Max GC roots stack size: 31 roots

------------------------------------------------------------
Stella runtime statistics:
Total allocated fields in Stella objects: 65 fields

```