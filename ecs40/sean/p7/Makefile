songs.out: main.o song.o
	g++ -Wall -ansi  -o songs.out main.o song.o 

main.o: main.cpp song.h 
	g++ -Wall -ansi  -c main.cpp

song.o: song.cpp song.h 
	g++ -Wall -ansi  -c song.cpp

clean:
	rm -f songs.out main.o song.o 
