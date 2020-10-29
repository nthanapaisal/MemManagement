#makefile

clean:
	rm -f *.o part1 part2 part3
	
#compile
part1.o: part1.c
	gcc -c part1.c -o part1.o
part2.o: part2.c part2.h
	gcc -c part2.c -o part2.o
part3.o: part3.c part2.h
	gcc -c part3.c -o part3.o -lm
phypages.o: phypages.c part2.h
	gcc -c phypages.c -o phypages.o
pagetable.o: pagetable.c part2.h
	gcc -c pagetable.c -o pagetable.o
	
#create exe
part1: part1.o 
	gcc -g -o part1 part1.o
part2: part2.o phypages.o pagetable.o
	gcc -g -o part2 part2.o phypages.o pagetable.o
part3: part2.o part3.o phypages.o pagetable.o
	gcc -g -o part3 part3.o phypages.o pagetable.o -lm
