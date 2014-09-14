#//Authors: Chistopher Chen (997549548), Wai Shing Yung (996936848)
#//"Live by the code, die by the code."
funix.out: directory.o funix.o main.o permissions.o
	g++ -Wall -ansi -g -o funix.out directory.o funix.o main.o permissions.o 

directory.o: directory.cpp directory.h 
	g++ -Wall -ansi -g -c directory.cpp

funix.o: funix.cpp funix.h directory.h 
	g++ -Wall -ansi -g -c funix.cpp

main.o: main.cpp funix.h 
	g++ -Wall -ansi -g -c main.cpp

permissions.o: permissions.cpp permissions.h 
	g++ -Wall -ansi -g -c permissions.cpp

clean:
	rm -f funix.out directory.o funix.o main.o permissions.o 
