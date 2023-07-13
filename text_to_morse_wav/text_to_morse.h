#ifndef WAVFILE_H
#define WAVFILE_H

#define PI 3.14159265358979323846

#include "wavfile.h"
#include "wavfile.c"

#define MAX_FILENAME 80
#define MAX_CHARS    55
#define MAX_CHAR_SEQ 8
#define MAX_ASCII    127
#define MAX_SIGNAL_LENGTH WAVFILE_SAMPLES_PER_SECOND

/* CONSTANTS - we might want to change those */
const double default_frequency = 800.0;
const int default_rate_wpm = 12; 

/* FUNCTION PROTOTYPES */
void write_tone(FILE *outfile, short waveform[],
		double frequency, int duration);

void write_silence(FILE *outfile, short waveform[], int duration);

void write_morse_char(FILE *outfile, short waveform[],
		      double frequency, double unit_duration,
		      int signal_code[]);

const enum { MSG_HELP, MSG_VERSION, MSG_ERROR } msg_code;
const enum { DOT, DASH, CHAR_SPC, WORD_SPC, ENDCODE } sign_type;

#endif