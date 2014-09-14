calc.out : main.o bitops.o
	gcc -Wall  -o calc.out main.o bitops.o

main.o : main.c bitops.h
	gcc -Wall  -c main.c

bitops.o : bitops.c bitops.h
	gcc -Wall  -c bitops.c

