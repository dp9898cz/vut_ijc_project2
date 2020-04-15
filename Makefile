C=gcc -std=c99 -pedantic -Wall -Wextra -g
CPP=g++ -std=c++11 -pedantic -Wall -g

all: tail

# tail program
tail: tail.o
	$(C) tail.o -o tail
tail.o: tail.c
	$(C) -c tail.c -o tail.o

#libhtab.a (static library)
libhtab: 

#clean
clean: 
	rm -f *.o tail