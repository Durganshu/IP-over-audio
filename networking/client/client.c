#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // Replace with the server IP address
#define PORT 12345
#define BUFFER_SIZE 1024

void send_file(FILE *file, int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        int bytes_sent = send(client_socket, buffer, bytes_read, 0);
        if (bytes_sent < 0) {
            perror("Error sending data");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    FILE *file;

    // Create a client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server at %s:%d\n", SERVER_IP, PORT);

    // Open the WAV file to be sent
    file = fopen("example_file.wav", "rb");
    if (!file) {
        perror("Error opening the WAV file");
        exit(EXIT_FAILURE);
    }

    // Send the WAV file to the server
    send_file(file, client_socket);

    fclose(file);
    printf("File sent successfully.\n");

    close(client_socket);

    return 0;
}
