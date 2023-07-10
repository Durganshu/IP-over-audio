#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "morse_base.h"
#include "morse_decoder.h"
#include "morse_encoder.h"

#define MAX_LENGTH 100

int main(void){

    make_tree();
    printf("--------------------------------------------------------\n");
    printf("Hey! Do you wanna encode/decode a Morse code?\n");
    printf("Press 1 for encoding a message into the Morse code\n");
    printf("Press 2 for decoding a Morse code\n");
    printf("--------------------------------------------------------\n\n");
    char dummy_input[2];
    int input;
    char input_message[MAX_LENGTH];
    fgets(dummy_input, 2, stdin);
    sscanf(dummy_input, "%d", &input);
    
    switch(input)
    {
        case 1:
            printf("--------------------------------------------------------\n\n");
            printf("Please enter the text message\n");
            getchar();
            fgets(input_message, MAX_LENGTH, stdin);
            printf("\nEncoding...\n\n");
            printf("Morse code: ");
            encode(input_message);
            printf("--------------------------------------------------------\n\n");
            break;
        case 2:
            printf("--------------------------------------------------------\n\n");
            printf("Please enter the Morse code\n");
            getchar();
            fgets(input_message, MAX_LENGTH, stdin);
            // printf("size of input_message= %ld\n", strlen(input_message));
            printf("\nDecoding...\n\n");
            printf("Message: ");
            decode(input_message);
            printf("--------------------------------------------------------\n\n");
            break;
        default:
            printf("Error!!! Please check your input. Exiting now!\n");
            exit(0);
    }

    // encode("Hello World");
    // decode( ".... . .-.. .-.. --- / .-- --- .-. .-.. -..");
    delete_tree();
    return 0;
}

