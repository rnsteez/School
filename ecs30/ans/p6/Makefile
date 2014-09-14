all: checksum.out election.out polygon.out

checksum.out: checksum.c 
	g++ -Wall -o checksum.out checksum.c

election.out: election.c 
	g++ -Wall -o election.out election.c

polygon.out: polygon.c 
	g++ -Wall -lm -o polygon.out polygon.c

clean:
	rm -f checksum.out election.out polygon.out 
