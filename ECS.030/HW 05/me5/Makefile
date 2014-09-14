# Wai Shing Yung 996936848

calc.out: main.o bitops.o
	gcc -Wall -g -o calc.out main.o bitops.o

main.o: main.c bitops.h
	gcc -Wall -c -g main.c

bitops.o: bitops.c bitops.h
	gcc -Wall -c -g bitops.c

