#include "networking.h"


int recvFile(char* buf, int s){
    int i;
    char ch;
    for (i = 0; i < s; i++) {
        ch = buf[i];
        if (ch == EOF)
            return 1;
    }
    return 0;
}


int udp_server_operations() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;

    len = sizeof(cliaddr); 
	char* filename = "received.wav";
	ssize_t rec;
    size_t written;

	// Creating a file.
	FILE* fp = fopen(filename, "wb"); //Opens the file for writing in binary mode.
    while (rec = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len) > 0) {
        // Writing the received bytes to the file.
		written = fwrite(buffer, 1, rec, fp);
        if (written != rec) {
            perror("Error while writing to file");
            fclose(fp);
            return 1;
        }
		
		bzero(buffer, BUFFER_SIZE);
		
		//printf("received %d bytes\n",n);

		// process

			//sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
		//	break;
		//}
    }
	fclose(fp);
	printf("File received!\n");
		

    return 0;
}