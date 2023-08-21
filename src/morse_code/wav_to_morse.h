#ifndef WAV_TO_MORSE_H
#define WAV_TO_MORSE_H

#define THRESHOLD 0.5 // Adjustable in case of need
#define MAX_SENTENCE_LENGTH 1024
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
} WavHeader;

typedef struct {
    int samples_group;
    int new_data_count;
    FILE* file;
} ConversionParameters;

char decode(char s[]);

void wav_to_morse(ConversionParameters *param, WavHeader head, char message[MAX_SENTENCE_LENGTH]);

#endif