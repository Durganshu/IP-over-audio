#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define IP_ADDRESS  "127.0.0.1"  
#define PORT_NUMBER 8080      
#define BUFFER_SIZE 1024
#define WAV_NAME "example_file.wav"
// function reading file in buffer
int readFile(FILE* fp, char* buf, int s)
{
    int i, len;
    char ch;
    for (i = 0; i < s; i++) {
        ch = fgetc(fp);
        buf[i] = ch;
        if (ch == EOF)
            return 1;
    }
    return 0;
}



int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create an UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    //serverAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	serverAddr.sin_port = htons(PORT_NUMBER);
    inet_pton(AF_INET, IP_ADDRESS, &serverAddr.sin_addr);

	ssize_t  n;
	socklen_t len;
	FILE* fp;
	fp = fopen(WAV_NAME, "r");
	while ( (n=fread(buffer,1, BUFFER_SIZE, fp))>0 ){
		//printf("sended %d bytes\n",n);
		// bzero(buffer, BUFFER_SIZE);
		// send
		ssize_t bytesSent = sendto(sockfd, buffer, BUFFER_SIZE,
		   0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		if (bytesSent == -1) {
            perror("Error sending data");
            break;
        }
    }
	//strcpy(buffer, "END");
	bzero(buffer, BUFFER_SIZE);
	sendto(sockfd, buffer, 0, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (fp != NULL)
        fclose(fp);
	
	
	close(sockfd);
    return 0;
}