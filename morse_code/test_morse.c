#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "morse_base.h"
#include "morse_decoder.h"
#include "morse_encoder.h"


int main(void){

    MTree *root;
    make_tree(root);
    encode_out("HELLO WORLD");
    encode_out("JOKE");
    decode_out(root, ".... . .-.. .-.. --- / .-- --- .-. .-.. -..");
    decode_out(root, ".--- --- -.- .");
    drop_tree(root);
    return 0;
}

