#Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
#"Live by the code, die by the code."

funix.out: file.o directory.o funix.o main.o permissions.o Time.o
	g++ -Wall -g -ansi -o funix.out file.o directory.o funix.o main.o permissions.o Time.o
	
file.o: file.cpp file.h
	g++ -Wall -g -ansi -c file.cpp

directory.o: directory.cpp directory.h file.h Time.h permissions.h linkedlist.h linkedlist.cpp
	g++ -Wall -g -ansi -c directory.cpp

funix.o: funix.cpp funix.h directory.h 
	g++ -Wall -g -ansi -c funix.cpp

main.o: main.cpp funix.h 
	g++ -Wall -g -ansi -c main.cpp

permissions.o: permissions.cpp permissions.h 
	g++ -Wall -g -ansi -c permissions.cpp

Time.o: Time.cpp Time.h 
	g++ -Wall -g -ansi -c Time.cpp
	
clean:
	rm -f funix.out file.o directory.o funix.o main.o permissions.o Time.o linkedlist.o
