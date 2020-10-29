This program simulated a process's memory management. 
 

Part1: Read in a sequential file, read 8 bytes at a time. Convert logical address to physical address using fixed mapping array.

Part2: Similar to part1 but Part2 can read in a file and writing to a using fixed sizes for logical bits, physical bits, page sizes.Convert logical address to physical address by using mapping into intial empty frames. The first accesses to frames are all in sequential order.
If frames are full, select LRU frame (keep track using reference bit). If page exists, copy page number and combine with offset of that address.

Part3: Similar to part2 but Part3 can read in a file and writing to a using CUSTOM sizes for logical bits, physical bits, page sizes

Compile into executable files using Makefile:
	Make part1 
	Make part2
	Make part3
	Make clean delete *.o
	
	Run:
	./part* whatever the parameters needed for that executable

Command line:
	gcc part1.c -i part1.o
	./part1.o infile outfile

	gcc part2.c phypages.c pagetable.c -i part1.o
	./part2.o infile outfile

	gcc part3.c phypages.c pagetable.c -i part1.o
	./part3.o pagesize logical physical infile outfile