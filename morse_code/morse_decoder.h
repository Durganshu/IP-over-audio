#ifndef MORSE_DECODER
#define MORSE_DECODER

#include "morse_base.h"

void decode_out_aux(MTree *tree, const char *s);

void decode_out(MTree *root, const char *s);

#endif