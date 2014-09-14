#Wai Shing Yung 996936848

rsvp.out: rsvp.o vector.o course.o
	gcc -Wall -g -o rsvo.out rsvp.o vector.o course.o

rsvp.o: rsvp.c course.h vector.h
	gcc -Wall -g -c rsvp.c

course.o: course.c vector.h
	gcc -Wall -g -c course.c

vector.o: vector.c 
	gcc -Wall -g -c vector.c

clean:
	rm -f vector.o course.o rsvp.o
