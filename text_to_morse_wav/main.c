#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include <math.h>
#include <time.h>
#include "text_to_morse.h"

const double default_frequency = 800.0;
const int default_rate_wpm = 12; 

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

/* Set default values */
double frequency = default_frequency;
int rate_wpm = default_rate_wpm;
double unit_duration = WAVFILE_SAMPLES_PER_SECOND / default_rate_wpm;
/* Array of numeric values for each tone's waveform */
int lower_upper_ascii_difference = 'a' - 'A';

FILE *input_file, *output_file, *output_text_file;
char input_file_name[MAX_FILENAME], output_file_name[MAX_FILENAME];

/* Set default values */
double frequency;
int rate_wpm;
double unit_duration;


/* Array of numeric values for each tone's waveform */
short waveform[MAX_SIGNAL_LENGTH];
/* Lookup table indexed to ASCII codes */
int ascii_table[MAX_ASCII];
int morse_table_index;
int *signal_code;
int ascii_char;
int lower_upper_ascii_difference;

void process_input(){
// void process_input(FILE *input_file, char *input_file_name){
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

}

void process_output(){
// void process_output(FILE *output_file, char *output_file_name, char *input_file_name){
    /* Open output file, using input file name with .wav extension */
	int i = strlen(output_file_name);
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
    output_text_file = fopen("output_text_file.txt", "w+");
}

void create_wav_file(){
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
		write_morse_char(output_file, waveform, frequency, unit_duration, signal_code, output_text_file);
	}
}

void close_files(){
    /* Close input and output files */
    fclose(input_file);
    fclose(output_file);
    fclose(output_text_file);
}

void play_output(){
    char command[7 + MAX_FILENAME];
	strcpy(command, "paplay ");
	printf("\nThis is your message in morse code:\n");
	output_text_file = fopen("output_text_file.txt", "r");
	int ch;
    while ((ch = fgetc(output_text_file)) != EOF) {
        putchar(ch); // Print the character to the console (or any other output stream)
    }
	printf("\nPlaying the audio file...\n");
	if (system(strcat(command, output_file_name)) < 0) {
		fprintf(stderr, "Could not play audio file %s.\n", output_file_name);
		exit(EXIT_FAILURE);
	}
    fclose(output_text_file);
}

int main(int argc, char *argv[]) 
{
	int i;

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

	// /* Open input file */
	// input_file = fopen(input_file_name, "r");
	// if (input_file == NULL) {
	// 	printf("\nCould not read file %s, let me create one instead.\n\n", input_file_name);
	// 	input_file = fopen(input_file_name, "w+");
	// 	if (input_file == NULL) {
	// 		fprintf(stderr, "Could not create file %s.\n", input_file_name);
	// 		exit(EXIT_FAILURE);
	// 	}

	// 	char command[7 + MAX_FILENAME];
	// 	strcpy(command, "cat >> ");
	// 	printf("What message would you like to send?\n\t(press [Ctrl] + [d] at the end of the message)\n");
		
	// 	if (system(strcat(command, input_file_name)) < 0) {
	// 		fprintf(stderr, "Could not write to file %s.\n", input_file_name);
	// 		exit(EXIT_FAILURE);
	// 	}
	// }

    process_input(input_file, input_file_name);

    strcpy(output_file_name, input_file_name);

    process_output(output_file, output_file_name, input_file_name);

	// /* Open output file, using input file name with .wav extension */
	// strcpy(output_file_name, input_file_name);
	// i = strlen(output_file_name);
	// if (output_file_name[i - 4] == '.') {
	// 	strcpy(&output_file_name[i - 3], "wav");
	// }
	// else {
	// 	fprintf(stderr,
	// 			"Bad format for file name %s, please provide a text file (.txt extension).\n", input_file_name);
	// 	exit(EXIT_FAILURE);
	// }

	// output_file = wavfile_open(output_file_name);
	// if (output_file == NULL) {
	// 	fprintf(stderr, "Could not write to file %s.\n", output_file_name);
	// 	exit(EXIT_FAILURE);
	// }

	/* Make lookup table to access morse codes through ASCII values */
	/* First make empty ASCII entries point to space character,
		which is last value of morse_table */
	for (i = 0; i < MAX_CHARS; i++) {
		ascii_char = morse_table[i][0]; //For example, if i=1 than the variable 'ascii_char' contains 'B'.
		ascii_table[ascii_char] = i; // The 66-th ('B' in ASCII) element of the 'ascii_table' array contains 1,
	}
	
	// output_text_file = fopen("output_text_file.txt", "w+");
    create_wav_file();
	// /* Read in characters, look up series of dots and dashes in sign
	// 	table, output appropriate format for each dot, dash, or space. */
	// while ((ascii_char = fgetc(input_file)) != EOF) {
	// 	/* Ensure valid input */
	// 	if (ascii_char > MAX_ASCII) {
	// 		break;
	// 	}
	// 	/* Ignore newlines, no processing needed */
	// 	else if (ascii_char == '\n') {
	// 		continue;
	// 	}
	// 	/* Convert lowercase to uppercase */
	// 	else if (ascii_char >= 'a' && ascii_char <= 'z') {
	// 		ascii_char -= lower_upper_ascii_difference; 
	// 	}
    
	// 	/* Get morse output patterns for each component character from lookup table */
	// 	morse_table_index = ascii_table[ascii_char];
	// 	signal_code = &morse_table[morse_table_index][1];
	// 	write_morse_char(output_file, waveform, frequency, unit_duration, signal_code, output_text_file);
	// }

    // Cleanup
    close_files();

	// fclose(input_file);
	// wavfile_close(output_file);
	// fclose(output_text_file);
    system("paplay hello.wav");
    // /* Play audio file */
    // play_output();
	char command[7 + MAX_FILENAME];
	strcpy(command, "paplay ");
	printf("\nThis is your message in morse code:\n");
	output_text_file = fopen("output_text_file.txt", "r");
	int ch;
    while ((ch = fgetc(output_text_file)) != EOF) {
        putchar(ch); // Print the character to the console (or any other output stream)
    }
	printf("\nPlaying the audio file...\n");
    
	if (system(strcat(command, output_file_name)) < 0) {
		fprintf(stderr, "Could not play audio file %s.\n", output_file_name);
		exit(EXIT_FAILURE);
	}

	return 0;
}
