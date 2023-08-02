all: fancy_hello
 
fancy_hello: fancy_hello.o
	cc -g -o fancy_hello fancy_hello.o
 
fancy_hello.o: fancy_hello.c fancy_hello.h
	cc -c -Wall -g fancy_hello.c 
 
clean:
	rm fancy_hello.o fancy_hello