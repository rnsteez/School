#Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
#"Live by the code, die by the code."

songs.out: songs.o main.o
	g++ -Wall -g -ansi -o songs.out songs.o main.o
	
songs.o: songs.cpp songs.h
	g++ -Wall -g -ansi -c songs.cpp
	
main.o: main.cpp songs.h
	g++ -Wall -g -ansi -c main.cpp
	
clean:
	rm -f songs.out songs.o main.o
