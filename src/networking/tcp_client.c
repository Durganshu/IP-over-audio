#include "networking.h"

int client_socket;
struct sockaddr_in server_addr;

int tcp_start_client(char ip_address[]) {
    // Create a client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    printf("Connected to the server at %s:%d\n", ip_address, PORT);

    return client_socket;
}

void tcp_send(char text_file[])
{
    // Send the WAV file to the server
    send_file(text_file, client_socket);

}
