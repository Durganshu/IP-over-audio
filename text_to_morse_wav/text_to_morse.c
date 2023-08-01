/**
 * text_to_morse.c -- Convert ASCII text to Morse code audio.
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include <math.h>
#include <time.h>
#include "text_to_morse.h"
const enum sign_type_enum sign_type = DOT;

// In the original github repo I found, there is an option
// for the user to set the frequency, rate, and output file name.

void write_tone(FILE *outfile, short waveform[], double frequency, int duration) {
	int i;
	double timepoint;
	int volume = 32000;
	for (i = 0; i < duration; ++i) {
		timepoint = (double) i / WAVFILE_SAMPLES_PER_SECOND;
		waveform[i] = volume * sin(frequency * timepoint * 2 * PI);
	}
	wavfile_write(outfile, waveform, duration);
	
	return;
}


void write_silence(FILE *output_file, short waveform[], int duration) {
	for (int i = 0; i < duration; ++i) {
		waveform[i] = 0;
	}
	wavfile_write(output_file, waveform, duration);

	return;
}


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
void write_morse_char(FILE *output_file, short waveform[], double frequency,
						double unit_duration, int signal_code[], FILE *output_text_file) {
	int i;
	for (i = 0; signal_code[i] != ENDCODE; i++) {
		if (signal_code[i] == WORD_SPC) {
			/* Write space between words */
			write_silence(output_file, waveform, 6 * unit_duration);
			fprintf(output_text_file, "/");
			break;
		}
		else if (signal_code[i] == DOT) {
			/* Write dot */
			write_tone(output_file, waveform, frequency, unit_duration);
			fprintf(output_text_file, ".");
		}
		else {
			/* Write dash */
			write_tone(output_file, waveform, frequency, 3 * unit_duration);
			fprintf(output_text_file, "-");
		}
		/* Write inter-signal space (between the dots and dashes that represent a character) */
		write_silence(output_file, waveform, unit_duration);

	}
	/* Write inter-character space */
	write_silence(output_file, waveform, 2 * unit_duration);
	fprintf(output_text_file, " ");

	return;
}
  