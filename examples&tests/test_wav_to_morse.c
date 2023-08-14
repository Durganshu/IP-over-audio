#include <stdio.h>
#include <string.h>
#include "morse_core.h"

// double* pcm_data;
// int num_samples, sample_rate;

// WavHeader header;
// ConversionParameters params;

// // FILE* file;
// // Read audio file
// const char* filename = "example_file.wav";

// void read_Wav_file(){

//     params.file = fopen(filename, "rb");
//     if (!params.file) {
//         printf("Error opening file\n");
//         return 1;
//     }

//     // Read WAV file header
//     fread(&header, sizeof(WavHeader), 1, params.file);
//     printf("Length %d \n",header.bytes_in_data);
//     printf("sampleRate %d \n",header.sampleRate);
//     printf("bytes_per_second %d \n",header.bytes_per_second);
//     printf("bytes_by_capture %d \n",header.bytes_by_capture);
//     printf("bits_per_sample %d \n",header.bits_per_sample);

// }

int main() {

    read_Wav_file();

    convert_Wav_to_morse();
    
    // read_Wav_file();
    // params.samples_group = header.sampleRate/50;
    // params.new_data_count = (header.bytes_in_data/header.bytes_by_capture)/params.samples_group;
    // int new_data[params.new_data_count];
    

    // // converts samples to 0, 1
    // for (int j = 0; j<params.new_data_count; j++) {
    //     int sum=0;
    //     for (int i = 0; i < params.samples_group; i++) {
    //         fread(&params.x, header.bytes_by_capture, 1, params.file);
    //         if (params.x > 0) sum += params.x;
    //         else sum -= params.x;
    //     }
    //     if (sum>params.samples_group*50) new_data[j] = 1;
    //     else new_data[j] = 0;
    // }

    // // detecting minimal sequence of 0 (for letter pause) and 1 (for dot)
    // // maximum sequence of 1 (for dash)
    // int min[2];
    // int max[2];
    // params.x = new_data[0];
    // int count = 0;
    // for (int j = 0; j<params.new_data_count; j++) {
    //     if (new_data[j] == params.x) count++;
    //     else {
    //         if (count>max[params.x]) max[params.x] = count;
    //         if (count<min[params.x]) min[params.x] = count;
    //         count = 1;
    //         params.x = new_data[j];
    //     }
    // }
    // int pause_letter = 2*min[0]-1;
    // int pause_word = max[0] - min[0];
    // int dash = (max[1]+min[1])/2;

    // params.x = new_data[0];
    // count = 0;

    // for (int j = 0; j<params.new_data_count; j++) {
    //     if (new_data[j] == params.x) count++;
    //     else {
    //         if (params.x==1){
    //             if (count>dash){
    //                 printf("-");
    //             }
    //             else{
    //                 printf(".");
    //             }
    //         }
    //         else{
    //             if (count>pause_letter){
    //                 //new word
    //                 printf(" ");
    //             }
    //             if (count>pause_word){
    //                 // new sentence
    //                 printf(" \n");
    //             }
    //         }
    //         count = 1;
    //         params.x =  new_data[j];
    //     }
    // }



    // Decode Morse code into text

    // Free allocated memory
    //free(pcm_data);

    return 0;
}


