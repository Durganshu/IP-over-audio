/**
 * Built upon the examples from Andrew A. Cashner:
 * https://github.com/andrewacashner/
 * 
 * This program uses Douglas Thain's sound library:
 * http://www.nd.edu/~dthain/course/cse20211/fall2013/wavfile
 * 
*/

#ifndef TEXT_TO_MORSE_H
#define TEXT_TO_MORSE_H

#define PI 3.14159265358979323846

#include "../core_functionality/wavfile.h"

#define MAX_FILENAME 80
#define MAX_CHARS    55
#define MAX_CHAR_SEQ 8
#define MAX_ASCII    127
#define MAX_SIGNAL_LENGTH WAVFILE_SAMPLES_PER_SECOND

extern const double default_frequency;
extern const int default_rate_wpm; 

/* FUNCTION PROTOTYPES */
void write_tone(FILE *outfile, short waveform[],
		double frequency, int duration);

void write_silence(FILE *outfile, short waveform[], int duration);

/**
 * Translates a character to morse code according to the morse table we defined,
 * then writes the morse to the output .wav file given as an argument.
 * The morse code in the .wav file will be represented as follows:
 * 	- A dot is represented by a beep of 1 time unit.
 * 	- A dash is represented by a beep of 3 time units.
 * 	- A separation between morse signals of a character is represented by a silence of 1 time unit.
 * 	- A separation between characters of the same word is represented by a silence of 2 time unit.
 * 	- A space between words is represented by a silence of 6 time units.
*/
void write_morse_char(FILE *outfile, short waveform[],
		      double frequency, double unit_duration,
		      int signal_code[], FILE *output_text_file);

enum sign_type_enum {
    DOT, DASH, CHAR_SPC, WORD_SPC, ENDCODE
};

extern const enum sign_type_enum sign_type;

/* Lookup table of morse signal codes */
extern int morse_table[MAX_CHARS][MAX_CHAR_SEQ + 1];

#endif