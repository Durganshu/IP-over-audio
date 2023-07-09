#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse_decoder.h"

void decode_out_aux(MTree *tree, const char *s){
    if(tree == NULL) return;
    if(*s == '\0')
        fputc(tree->value, stdout);
    else if(*s == '/')
        fputc(' ', stdout);
    else if(*s == '.')
        decode_out_aux(tree->dot, ++s);
    else if(*s == '-')
        decode_out_aux(tree->bar, ++s);
}

void decode_out(MTree *root, const char *s){
    char *p;
    while(*s){
        p = strchr(s, ' ');
        if(p){
            if(p-s != 0){
                char code[p-s+1];
                memcpy(code, s, p-s);
                code[p-s]='\0';
                decode_out_aux(root, code);
            }
            s = p + 1;
        } else {
            decode_out_aux(root, s);
            break;
        }
    }
    fputc('\n', stdout);
}

