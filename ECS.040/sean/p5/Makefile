funix.out: directory.o funix.o linkedlist.o main.o permissions.o Time.o
	g++ -Wall -g -ansi -o funix.out directory.o funix.o linkedlist.o main.o permissions.o Time.o 

directory.o: directory.cpp directory.h Time.h permissions.h 
	g++ -Wall -g -ansi -c directory.cpp

funix.o: funix.cpp funix.h directory.h 
	g++ -Wall -g -ansi -c funix.cpp

linkedlist.o: linkedlist.cpp linkedlist.h directory.h 
	g++ -Wall -g -ansi -c linkedlist.cpp

main.o: main.cpp funix.h 
	g++ -Wall -g -ansi -c main.cpp

permissions.o: permissions.cpp permissions.h 
	g++ -Wall -g -ansi -c permissions.cpp

Time.o: Time.cpp Time.h 
	g++ -Wall -g -ansi -c Time.cpp

clean:
	rm -f funix.out directory.o funix.o linkedlist.o main.o permissions.o Time.o 
