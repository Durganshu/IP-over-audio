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
#include "wavfile.c"

// In the original github repo I found, there is an option
// for the user to set the frequency, rate, and output file name.

int main(int argc, char *argv[]) 
{
	/* Set default values */
	double frequency = default_frequency;
	int rate_wpm = default_rate_wpm;
	double unit_duration = WAVFILE_SAMPLES_PER_SECOND / default_rate_wpm;

	FILE *input_file, *output_file;
	char input_file_name[MAX_FILENAME], output_file_name[MAX_FILENAME];

	/* Array of numeric values for each tone's waveform */
	short waveform[MAX_SIGNAL_LENGTH];

	/* Lookup table indexed to ASCII codes */
	int ascii_table[MAX_ASCII];
	int morse_table_index;
	int *signal_code;

	int i, ascii_char;
	int lower_upper_ascii_difference = 'a' - 'A';

	if (argc > 2) {
		fprintf(stderr, "Too many arguments.\n\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2) {
		strcpy(input_file_name, argv[1]);
	}
	else {
		fprintf(stderr, "No input file specified.\n\n");
		exit(EXIT_FAILURE);
	}

	/* Open input file */
	input_file = fopen(input_file_name, "r");
	if (input_file == NULL) {
		printf("\nCould not read file %s, let me create one instead.\n\n", input_file_name);
		input_file = fopen(input_file_name, "w+");
		if (input_file == NULL) {
			fprintf(stderr, "Could not create file %s.\n", input_file_name);
			exit(EXIT_FAILURE);
		}

		char command[7 + MAX_FILENAME];
		strcpy(command, "cat >> ");
		printf("What message would you like to send?\n\t(press [Ctrl] + [d] at the end of the message)\n");
		
		if (system(strcat(command, input_file_name)) < 0) {
			fprintf(stderr, "Could not write to file %s.\n", input_file_name);
			exit(EXIT_FAILURE);
		}
	}

	/* Open output file, using input file name with .wav extension */
	strcpy(output_file_name, input_file_name);
	i = strlen(output_file_name);
	if (output_file_name[i - 4] == '.') {
		strcpy(&output_file_name[i - 3], "wav");
	}
	else {
		fprintf(stderr,
				"Bad format for file name %s, please provide a text file (.txt extension).\n", input_file_name);
		exit(EXIT_FAILURE);
	}

	output_file = wavfile_open(output_file_name);
	if (output_file == NULL) {
		fprintf(stderr, "Could not write to file %s.\n", output_file_name);
		exit(EXIT_FAILURE);
	}

	/* Make lookup table to access morse codes through ASCII values */
	/* First make empty ASCII entries point to space character,
		which is last value of morse_table */
	for (i = 0; i < MAX_CHARS; i++) {
		ascii_char = morse_table[i][0]; //For example, if i=1 than the variable 'ascii_char' contains 'B'.
		ascii_table[ascii_char] = i; // The 66-th ('B' in ASCII) element of the 'ascii_table' array contains 1,
	}
  
	/* Read in characters, look up series of dots and dashes in sign
		table, output appropriate format for each dot, dash, or space. */
	while ((ascii_char = fgetc(input_file)) != EOF) {
		/* Ensure valid input */
		if (ascii_char > MAX_ASCII) {
			break;
		}
		/* Ignore newlines, no processing needed */
		else if (ascii_char == '\n') {
			continue;
		}
		/* Convert lowercase to uppercase */
		else if (ascii_char >= 'a' && ascii_char <= 'z') {
			ascii_char -= lower_upper_ascii_difference; 
		}
    
		/* Get morse output patterns for each component character from lookup table */
		morse_table_index = ascii_table[ascii_char];
		signal_code = &morse_table[morse_table_index][1];
		write_morse_char(output_file, waveform, frequency, unit_duration, signal_code);
	}

	fclose(input_file);
	wavfile_close(output_file);

	char command[7 + MAX_FILENAME];
	strcpy(command, "paplay ");
	printf("\nThis is your message in morse code:\n");
	if (system(strcat(command, output_file_name)) < 0) {
		fprintf(stderr, "Could not play audio file %s.\n", output_file_name);
		exit(EXIT_FAILURE);
	}

	return 0;
}


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
						double unit_duration, int signal_code[]) {
	int i;
	for (i = 0; signal_code[i] != ENDCODE; i++) {
		if (signal_code[i] == WORD_SPC) {
			/* Write space between words */
			write_silence(output_file, waveform, 6 * unit_duration);
			break;
		}
		else if (signal_code[i] == DOT) {
			/* Write dot */
			write_tone(output_file, waveform, frequency, unit_duration);
		}
		else {
			/* Write dash */
			write_tone(output_file, waveform, frequency, 3 * unit_duration);
		}
		/* Write inter-signal space (between the dots and dashes that represent a character) */
		write_silence(output_file, waveform, unit_duration);
	}
	/* Write inter-character space */
	write_silence(output_file, waveform, 2 * unit_duration);

	return;
}
  