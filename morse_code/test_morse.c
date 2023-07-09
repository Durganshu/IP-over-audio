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
    encode("Durganshu");
    encode("Mishra");
    decode( "-.. ..- .-. --. .- -. ... .... ..- / -- .. ... .... .-. .-");
    drop_tree();
    return 0;
}

