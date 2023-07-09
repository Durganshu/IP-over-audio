#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse_encoder.h"

void encode_out(const char *s){
    for(;;++s){
        char ch = *s;
        if(ch == '\0')
            break;
        if(isalpha(ch)){
            ch = toupper(ch);
            fputs(table[ALPHA][ch - 'A'], stdout);//`-'A'` depend on the sequence of character code
        } else if(isdigit(ch))
            fputs(table[NUM][ch - '0'], stdout);
        else if(ch == ' ')
            fputc('/', stdout);//need rest space skip ?
        fputc(' ', stdout);
    }
    fputc('\n', stdout);
}