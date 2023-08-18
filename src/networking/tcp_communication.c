#include "networking.h"

int send_response(int socket) {
    char buffer[BUFFER_SIZE];
    int buffer_size = strlen(RECEIVED_VALIDATION);
    strcpy(buffer, RECEIVED_VALIDATION);
    // Send the size of the file as a length indicator
    if (send(socket, &buffer_size, sizeof(buffer_size), 0) < 0) {
        perror("Error sending buffer size");
        exit(EXIT_FAILURE);
    }
    if (send(socket, buffer, sizeof(buffer), 0) < 0){
        printf("Couldn't send the response to the client\n");
        return ERROR;
    }
    return 0;
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
    long recv_buffer_size;
    printf("Waiting for response from the other computer...\n");
    int buffer_received = recv(socket, &recv_buffer_size, sizeof(recv_buffer_size), 0);
    if (buffer_received != sizeof(recv_buffer_size)) {
        perror("Error receiving file size");
        exit(EXIT_FAILURE);
    }

    int bytes_left = (int) recv_buffer_size;
    while (bytes_left > 0) {
        int bytes_to_receive = (bytes_left < BUFFER_SIZE) ? bytes_left : BUFFER_SIZE;
        buffer_received = recv(socket, response, BUFFER_SIZE, 0);
        if (buffer_received <= 0) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        }
        fwrite(response, 1, buffer_received, response_file);
        bytes_left -= buffer_received;
    }

    // int bytes_received;
    // while ((bytes_received = recv(socket, response, BUFFER_SIZE, 0)) > 0) {
    //     fwrite(response, 1, bytes_received, response_file);
    // }

    fclose(response_file);
    printf("Other computer's response: %s\n", response);
    printf("Response from the other computer received and saved as 'response.txt'\n");
}

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

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send the size of the file as a length indicator
    if (send(socket, &file_size, sizeof(file_size), 0) < 0) {
        perror("Error sending file size");
        exit(EXIT_FAILURE);
    }

    // Send the file data in chunks
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

    // Receive the size of the file as a length indicator
    long file_size;
    int bytes_received = recv(socket, &file_size, sizeof(file_size), 0);
    if (bytes_received != sizeof(file_size)) {
        perror("Error receiving file size");
        exit(EXIT_FAILURE);
    }

    // Open the file for writing
    received_file = fopen("received.wav", "wb");
    if (!received_file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int bytes_left = file_size;
    while (bytes_left > 0) {
        int bytes_to_receive = (bytes_left < BUFFER_SIZE) ? bytes_left : BUFFER_SIZE;
        bytes_received = recv(socket, buffer, bytes_to_receive, 0);
        if (bytes_received <= 0) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        }
        fwrite(buffer, 1, bytes_received, received_file);
        bytes_left -= bytes_received;
    }

    fclose(received_file);
    printf("File received and saved as 'received.wav'\n");

    send_response(socket);
}

void shutdown_connection(int socket) {
    close(socket);
}