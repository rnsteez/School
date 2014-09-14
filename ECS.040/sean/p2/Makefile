funix.out: directory.o funix.o main.o permissions.o
	g++ -Wall -ansi  -o funix.out directory.o funix.o main.o permissions.o 

directory.o: directory.c directory.h 
	g++ -Wall -ansi  -c directory.c

funix.o: funix.c funix.h directory.h 
	g++ -Wall -ansi  -c funix.c

main.o: main.c funix.h 
	g++ -Wall -ansi  -c main.c

permissions.o: permissions.c permissions.h 
	g++ -Wall -ansi  -c permissions.c

clean:
	rm -f funix.out directory.o funix.o main.o permissions.o 
