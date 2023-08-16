#ifndef NETWORKING_H
#define NETWORKING_H


#define BUFFER_SIZE 1024
#define PORT 54321
#define ERROR 1
#define SUCCESS 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


// UDP:
#include <unistd.h>
#include <sys/types.h>

int recv_file(char* buf, int s);
int udp_start_server();

void udp_handle_request();

int udp_start_client(char ip_address[]);

void udp_send(char audio_file[]);


// TCP:
#define RECEIVED_VALIDATION "The server has received your message.\n"
// int read_file(FILE* fp, char* buf, int s);
int send_response(int socket);
void receive_response(int socket);
void send_file(char text_file[], int socket);
void receive_message(int socket);
void shutdown_connection(int socket);

int tcp_start_server();

void tcp_handle_request();

int tcp_start_client( char ip_address[]);
void tcp_send(char text_file[]);

#endif