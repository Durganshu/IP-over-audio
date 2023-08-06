all: server fancyclient
 
server.o: server.c
	cc -c -Wall -g server.c 
	
fancyclient.o: fancyclient.c
	cc -c -Wall -g fancyclient.c 
	
server: server.o
	cc -g -o server server.o
	
fancyclient: fancyclient.o
	cc -g -o fancyclient fancyclient.o	

 
clean:
	rm server.o server
	rm fancyclient.o fancyclient