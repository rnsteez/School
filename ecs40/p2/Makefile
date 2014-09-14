#Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
#"Live by the code, die by the code."
# The code must die!

funix.out: main.o funix.o permissions.o directory.o
	g++ -Wall -ansi -g -o funix.out main.o funix.o permissions.o directory.o

main.o: main.c funix.h
	g++ -Wall -ansi -g -c main.c

funix.o: funix.c funix.h permissions.h directory.h
	g++ -Wall -ansi -g -c funix.c
   
directory.o: directory.c funix.h permissions.h directory.h
	g++ -Wall -ansi -g -c directory.c
   
permissions.o: permissions.c permissions.h funix.h
	g++ -Wall -ansi -g -c permissions.c

clean:
	rm -f *.o 
