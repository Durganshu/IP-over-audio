#include "networking.h"


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
    printf("File sent successfully.\n");    

    receive_server_response(client_socket);
}


void receive_server_response(int client_socket) {
    // Receive the server's response:
    char response[BUFFER_SIZE];
    memset(response, 0, BUFFER_SIZE);
    FILE *response_file;

    response_file = fopen("response.txt", "wb");
    if (!response_file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int bytes_received;
    while ((bytes_received = recv(client_socket, response, BUFFER_SIZE, 0)) > 0) {
        fwrite(response, 1, bytes_received, response_file);
    }

    fclose(response_file);
    printf("Server's response: %s\n", response);
    printf("Response from server received and saved as 'response.txt'\n");
}


int start_tcp_client(char text_file[], char ip_address[]) {
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

    // Open the WAV file to be sent
    file = fopen(text_file, "rb");
    if (!file) {
        perror("Error opening the WAV file");
        exit(EXIT_FAILURE);
    }

    // Send the WAV file to the server
    send_file(file, client_socket);    
    fclose(file);

    return 0;
}


void shutdown_connection(int client_socket) {
    close(client_socket);
}
