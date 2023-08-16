#include "networking.h"


int start_tcp_client(char text_file[], char ip_address[]) {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create a client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server at %s:%d\n", ip_address, PORT);

    // Send the WAV file to the server
    send_file(text_file, client_socket);

    return 0;
}
