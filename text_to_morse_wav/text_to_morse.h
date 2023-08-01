/**
 * text_to_morse.h -- Convert ASCII text to Morse code audio.
 * 
 * Based on code by Andrew A. Cashner:
 * https://github.com/andrewacashner/txt2morse/tree/master
 * This program uses Douglas Thain's sound library:
 * http://www.nd.edu/~dthain/course/cse20211/fall2013/wavfile
 * 
 * The program reads in text from a file,
 * converts the text to morse code,
 * and outputs the result as an audio file of the .wav extension.
*/

#ifndef TEXT_TO_MORSE_H
#define TEXT_TO_MORSE_H

#define PI 3.14159265358979323846

#include "wavfile.h"

#define MAX_FILENAME 80
#define MAX_CHARS    55
#define MAX_CHAR_SEQ 8
#define MAX_ASCII    127
#define MAX_SIGNAL_LENGTH WAVFILE_SAMPLES_PER_SECOND

/* CONSTANTS - we might want to change those */
extern const double default_frequency;
extern const int default_rate_wpm; 

/* FUNCTION PROTOTYPES */
void write_tone(FILE *outfile, short waveform[],
		double frequency, int duration);

void write_silence(FILE *outfile, short waveform[], int duration);

void write_morse_char(FILE *outfile, short waveform[],
		      double frequency, double unit_duration,
		      int signal_code[], FILE *output_text_file);

// const enum { DOT, DASH, CHAR_SPC, WORD_SPC, ENDCODE } sign_type;

enum sign_type_enum {
    DOT, DASH, CHAR_SPC, WORD_SPC, ENDCODE
};

extern const enum sign_type_enum sign_type;

/* Lookup table of morse signal codes */
extern int morse_table[MAX_CHARS][MAX_CHAR_SEQ + 1];

#endif