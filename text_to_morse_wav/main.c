#include "morse_core.h"

int main(int argc, char *argv[]) 
{

	initialize_params(argc, argv);

    process_input();

    strcpy(params.output_file_name, params.input_file_name);

    process_output();

	/* Make lookup table to access morse codes through ASCII values */
	/* First make empty ASCII entries point to space character,
		which is last value of morse_table */
	for (int i = 0; i < MAX_CHARS; i++) {
		params.ascii_char = morse_table[i][0]; //For example, if i=1 than the variable 'ascii_char' contains 'B'.
		params.ascii_table[params.ascii_char] = i; // The 66-th ('B' in ASCII) element of the 'ascii_table' array contains 1,
	}

    create_wav_file();

    // Cleanup
    close_files();

    // /* Play audio file */
    play_output();

	return 0;
}
