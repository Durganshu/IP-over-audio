#ifndef WAV_TO_MORSE_H
#define WAV_TO_MORSE_H

#define BUFFER_SIZE 1024

#define THRESHOLD 0.5 // Adjust this threshold according to your audio
#include <stdio.h>

typedef struct {
    char   id[4];            // should always contain "RIFF"
    int    totallength;      // total file length minus 8
    char   wavefmt[8];       // should be "WAVEfmt "
    int    format;           // 16 for PCM format
    short  pcm;              // 1 for PCM format
    short  channels;         // channels
    int    sampleRate;        // sampling frequency
    int    bytes_per_second;
    short  bytes_by_capture;
    short  bits_per_sample;
    char   data[4];          // should always contain "data"
    int    bytes_in_data;
}WavHeader;

typedef struct {

    int samples_group;
    int new_data_count;
    FILE* file;
}ConversionParameters;

char* decode(char* s);

// void wav_to_morse(struct ConversionParameters *param, struct WavHeader *head);
char* wav_to_morse(ConversionParameters param, WavHeader head);


#endif