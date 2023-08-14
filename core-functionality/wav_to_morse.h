#ifndef WAV_TO_MORSE_H
#define WAV_TO_MORSE_H

#define BUFFER_SIZE 1024

#define THRESHOLD 0.5 // Adjust this threshold according to your audio
#include <stdio.h>

struct WavHeader{
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
};

struct ConversionParameters{
    int sample_rate;
    int num_samples;
    double* pcm_data;
    int samples_group;
    int new_data_count;
    short x;
    FILE* file;
};

char* decode(char* s);

// void wav_to_morse(struct ConversionParameters *param, struct WavHeader *head);
void wav_to_morse(struct ConversionParameters param, struct WavHeader head);


#endif