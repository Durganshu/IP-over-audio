#ifndef MORSE_CORE_H
#define MORSE_CORE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include <math.h>
#include <time.h>
#include "text_to_morse.h"

struct Parameters {
    /* Set default values */
    double frequency;
    int rate_wpm;
    double unit_duration;
    /* Array of numeric values for each tone's waveform */
    int lower_upper_ascii_difference;

    FILE *input_file, *output_file, *output_text_file;
    char input_file_name[MAX_FILENAME], output_file_name[MAX_FILENAME];

    /* Array of numeric values for each tone's waveform */
    short waveform[MAX_SIGNAL_LENGTH];
    /* Lookup table indexed to ASCII codes */
    int ascii_table[MAX_ASCII];
    int morse_table_index;
    int *signal_code;
    int ascii_char;
};


// void initialize_params();


// void process_input();

// void process_output();

// void create_wav_file();

// void close_files();

// void play_output();

#endif