#ifndef IP_OVER_MORSE_H
#define IP_OVER_MORSE_H

#include "morse_code/morse_core.h"
#include "networking/networking.h"

#define DEFAULT_PORT 54321
#define DEFAULT_ADDRESS "127.0.0.1"

#define UDP_CLIENT 0
#define UDP_SERVER 1
#define TCP_CLIENT 2
#define TCP_SERVER 3

void print_help(char* prg, bool printHeader);
void parse_args(int argc, char* argv[]);
char* get_wav_file();
void decode_wav_file(char message[MAX_SENTENCE_LENGTH]);
void print_info_and_message(char message[MAX_SENTENCE_LENGTH]);

#endif