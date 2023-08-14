#include "morse_core.h"

int main(int argc, char *argv[]) 
{
	
	initialize_params(argc, argv);

	/**
	 * TODO:
	 * 
	 * If the user chose to be a client,
	 * they need to provide a file name and ip address to send the output to.
	 * 
	 * If it's in udp, call the function:
	 * start_udp_client(audio_file_name, ip_address)
	 * 
	 * If it's in tcp, call the function:
	 * start_tcp_client(text_file_name, ip_address)
	 * 
	 * 
	 * If the user chose to be a server -
	 * 
	 * If it's in udp, call the function:
	 * start_udp_server()
	 * 
	 * If it's in tcp, call the function:
	 * start_tcp_server()
	*/

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

	printf("Now reading wav file:\n");
	
	read_Wav_file();

    convert_Wav_to_morse();

	printf("\n");

	return 0;
}
