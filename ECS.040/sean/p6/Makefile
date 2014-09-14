funix.out: directory.o funix.o main.o permissions.o Time.o file.o
	g++ -Wall -ansi -o funix.out directory.o funix.o file.o main.o permissions.o Time.o 

directory.o: directory.cpp directory.h Time.h permissions.h 
	g++ -Wall -ansi -c directory.cpp

funix.o: funix.cpp funix.h directory.h 
	g++ -Wall -ansi -c funix.cpp

file.o: file.cpp permissions.h Time.h file.h
	g++ -Wall -ansi -c file.cpp

main.o: main.cpp funix.h 
	g++ -Wall -ansi -c main.cpp

permissions.o: permissions.cpp permissions.h 
	g++ -Wall -ansi -c permissions.cpp

Time.o: Time.cpp Time.h 
	g++ -Wall -ansi -c Time.cpp

clean:
	rm -f funix.out directory.o funix.o file.o linkedlist.o main.o permissions.o Time.o 
