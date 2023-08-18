#include "networking.h"

int sockfd;
struct sockaddr_in serverAddr;

int udp_start_client(char ip_address[]) {
    // int sockfd;
    // struct sockaddr_in serverAddr;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Could not create socket.\n");
        return ERROR;
    }
    
    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
    
    int err = inet_pton(AF_INET, ip_address, &serverAddr.sin_addr);
    if (err <= 0) {  // Inspired by "https://man7.org/linux/man-pages/man3/inet_pton.3.html"
        if (err == 0)
            fprintf(stderr, "Invalid address/Address not supported");
        else
            perror("inet_pton");
        return ERROR;
    }
    return 0;
}

void udp_send(char audio_file[])
{
    ssize_t bytes_read;
	ssize_t bytes_sent;
	socklen_t len;
	FILE* fp;
    char buffer[BUFFER_SIZE];

	fp = fopen(audio_file, "r");
	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
		bytes_sent = sendto(sockfd, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		if (bytes_sent < 0) {
            perror("Error sending data");
            break;
        }
        bzero(buffer, BUFFER_SIZE);
    }
	strcpy(buffer, "END");
	sendto(sockfd, buffer, 0, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (fp != NULL)
        fclose(fp);
	
    memset(buffer, 0, sizeof(buffer));

	bytes_read = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                            (struct sockaddr *) &serverAddr, &len);
	buffer[bytes_read] = '\0'; // Null-terminate the received message

	printf("Server's response: %s\n", buffer);
	close(sockfd);
}
