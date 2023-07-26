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

#ifndef TEXT_TO_MORSE
#define TEXT_TO_MORSE

#define PI 3.14159265358979323846

#include "wavfile.h"

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

const enum { DOT, DASH, CHAR_SPC, WORD_SPC, ENDCODE } sign_type;

/* Lookup table of morse signal codes */
int morse_table[MAX_CHARS][MAX_CHAR_SEQ + 1] = {
	{'A', DOT, DASH, ENDCODE },
	{'B', DASH, DOT, DOT, DOT, ENDCODE },
	{'C', DASH, DOT, DASH, DOT, ENDCODE },
	{'D', DASH, DOT, DOT, ENDCODE },
	{'E', DOT, ENDCODE },
	{'F', DOT, DOT, DASH, DOT, ENDCODE },
	{'G', DASH, DASH, DOT, ENDCODE },
	{'H', DOT, DOT, DOT, DOT, ENDCODE },
	{'I', DOT, DOT, ENDCODE },
	{'J', DOT, DASH, DASH, DASH, ENDCODE },
	{'K', DASH, DOT, DASH, ENDCODE },
	{'L', DOT, DASH, DOT, DOT, ENDCODE },
	{'M', DASH, DASH, ENDCODE },
	{'N', DASH, DOT, ENDCODE },
	{'O', DASH, DASH, DASH, ENDCODE },
	{'P', DOT, DASH, DASH, DOT, ENDCODE },
	{'Q', DASH, DASH, DOT, DASH, ENDCODE },
	{'R', DOT, DASH, DOT, ENDCODE },
	{'S', DOT, DOT, DOT, ENDCODE },
	{'T', DASH, ENDCODE },
	{'U', DOT, DOT, DASH, ENDCODE },
	{'V', DOT, DOT, DOT, DASH, ENDCODE },
	{'W', DOT, DASH, DASH, ENDCODE },
	{'X', DASH, DOT, DOT, DASH, ENDCODE },
	{'Y', DASH, DOT, DASH, DASH, ENDCODE },
	{'Z', DASH, DASH, DOT, DOT, ENDCODE },
	{'0', DASH, DASH, DASH, DASH, DASH, ENDCODE },
	{'1', DOT, DASH, DASH, DASH, DASH, ENDCODE },
	{'2', DOT, DOT, DASH, DASH, DASH, ENDCODE },
	{'3', DOT, DOT, DOT, DASH, DASH, ENDCODE },
	{'4', DOT, DOT, DOT, DOT, DASH, ENDCODE },
	{'5', DOT, DOT, DOT, DOT, DOT, ENDCODE },
	{'6', DASH, DOT, DOT, DOT, DOT, ENDCODE },
	{'7', DASH, DASH, DOT, DOT, DOT, ENDCODE },
	{'8', DASH, DASH, DASH, DOT, DOT, ENDCODE },
	{'9', DASH, DASH, DASH, DASH, DOT, ENDCODE },
	{'.', DOT, DASH, DOT, DASH, DOT, DASH, ENDCODE },
	{',', DASH, DASH, DOT, DOT, DASH, DASH, ENDCODE },
	{'?', DOT, DOT, DASH, DASH, DOT, DOT, ENDCODE },
	{'\'', DOT, DASH, DASH, DASH, DASH, DOT, ENDCODE },
	{'!', DASH, DOT, DASH, DOT, DASH, DASH, ENDCODE },
	{'/', DASH, DOT, DOT, DASH, DOT, ENDCODE },
	{'(', DASH, DOT, DASH, DASH, DOT, ENDCODE },
	{')', DASH, DOT, DASH, DASH, DOT, DASH, ENDCODE }, 
	{'&', DOT, DASH, DOT, DOT, DOT, ENDCODE },
	{':', DASH, DASH, DASH, DOT, DOT, DOT, ENDCODE },
	{';', DASH, DOT, DASH, DOT, DASH, DOT, ENDCODE },
	{'=', DASH, DOT, DOT, DOT, DASH, ENDCODE },
	{'+', DOT, DASH, DOT, DASH, DOT, ENDCODE },
	{'-', DASH, DOT, DOT, DOT, DOT, DASH, ENDCODE },
	{'_', DOT, DOT, DASH, DASH, DOT, DASH, ENDCODE },
	{'\"', DOT, DASH, DOT, DOT, DASH, DOT, ENDCODE },
	{'$', DOT, DOT, DOT, DASH, DOT, DOT, DASH, ENDCODE },
	{'@', DOT, DASH, DASH, DOT, DASH, DOT, ENDCODE },
	{' ', WORD_SPC, ENDCODE }
};

#endif