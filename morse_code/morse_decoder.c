#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse_decoder.h"

void decoder_aux(MTree *tree, const char *s){
    // printf("Char is = %s\n\n", s);
    if(tree == NULL) return;
    if(*s == '\0')
        fputc(tree->value, stdout);
    else if(*s == '/')
        fputc(' ', stdout);
    else if(*s == '.')
        decoder_aux(tree->dot, ++s);
    else if(*s == '-')
        decoder_aux(tree->bar, ++s);
}

void decode(const char *s){
    char *p;
    
    while(*s){

        p = strchr(s, ' ');
        
        if(p){
            if(p-s != 0){
                char code[p-s+1];
                memcpy(code, s, p-s);
                code[p-s]='\0';
                decoder_aux(root, code);
            }
            s = p + 1;
        } else {
            decoder_aux(root, s);
            break;
        }
    }
    
    fputc('\n', stdout);
}

