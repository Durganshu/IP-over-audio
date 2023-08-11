#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include <math.h>
#include <time.h>
#include "text_to_wav.h"
const enum sign_type_enum sign_type = DOT;


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
  