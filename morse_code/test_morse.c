#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "morse_base.h"
#include "morse_decoder.h"
#include "morse_encoder.h"


int main(void){

    make_tree();
    // encode_out("HELLO WORLD");
    // encode_out("JOKE");
    decode_out( ".... . .-.. .-.. --- / .-- --- .-. .-.. -..");
    decode_out(".--- --- -.- .");
    drop_tree();
    return 0;
}

