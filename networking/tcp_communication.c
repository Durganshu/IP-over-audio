#include "networking.h"


void send_file(char text_file[], int socket) {
    FILE *file;
    // Open the WAV file to be sent
    file = fopen(text_file, "rb");
    if (!file) {
        perror("Error opening the WAV file");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        int bytes_sent = send(socket, buffer, bytes_read, 0);
        if (bytes_sent < 0) {
            perror("Error sending data");
            exit(EXIT_FAILURE);
        }
    }
    printf("File sent successfully.\n");    

    receive_response(socket);
    fclose(file);
}


void receive_message(int socket) {
    FILE *received_file;
    char buffer[BUFFER_SIZE];

    // Receive the WAV file data from the client and save it to a file
    received_file = fopen("received.wav", "wb");
    if (!received_file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int bytes_received;
    while ((bytes_received = recv(socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, received_file);
    }

    fclose(received_file);
    printf("File received and saved as 'received.wav'\n");

    send_response(socket);
}


int send_response(int socket){
    if (send(socket, RECEIVED_VALIDATION, strlen(RECEIVED_VALIDATION), 0) < 0){
        printf("Couldn't send the response to the client\n");
        return ERROR;
    }
}


void receive_response(int socket) {
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
    while ((bytes_received = recv(socket, response, BUFFER_SIZE, 0)) > 0) {
        fwrite(response, 1, bytes_received, response_file);
    }

    fclose(response_file);
    printf("Other computer's response: %s\n", response);
    printf("Response from the other computer received and saved as 'response.txt'\n");
}


void shutdown_connection(int socket) {
    close(socket);
}