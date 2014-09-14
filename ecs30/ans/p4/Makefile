all: baseball.out beer.out data.out line.out

baseball.out: baseball.c 
	gcc -Wall  -g -o baseball.out baseball.c

beer.out: beer.c 
	gcc -Wall  -g -o beer.out beer.c

data.out: data.c 
	gcc -Wall  -g -lm -o data.out data.c

line.out: line.c 
	gcc -Wall  -g -o line.out line.c

clean:
	rm -f all baseball.out beer.c.out data.out line.out 
