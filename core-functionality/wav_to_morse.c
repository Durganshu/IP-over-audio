#include <stdio.h>
#include <string.h>

#include "wav_to_morse.h"

int detect_morse(double* pcm_data, int num_samples) {
    // Perform signal processing (e.g., FFT, peak detection) to detect Morse code pulses or tones
    // Here, we assume the Morse code pulses are represented as "1" and "0" otherwise.
    int i;
    for (i = 0; i < num_samples; i++) {
        if (pcm_data[i] > THRESHOLD)
            printf("1");
        else
            printf("0");
    }

    return 0;
}

// void wav_to_morse(struct ConversionParameters *param, struct WavHeader *head)
// {
//     int new_data[param->new_data_count];
    
//     // converts samples to 0, 1
//     for (int j = 0; j<param->new_data_count; j++) {
//         int sum=0;
//         for (int i = 0; i < param->samples_group; i++) {
//             fread(&param->x, head->bytes_by_capture, 1, param->file);
//             if (param->x > 0) sum += param->x;
//             else sum -= param->x;
//         }
//         if (sum>param->samples_group*50) new_data[j] = 1;
//         else new_data[j] = 0;
//     }

//     // detecting minimal sequence of 0 (for letter pause) and 1 (for dot)
//     // maximum sequence of 1 (for dash)
//     int min[2];
//     int max[2];
//     param->x = new_data[0];
//     int count = 0;
//     for (int j = 0; j<param->new_data_count; j++) {
//         if (new_data[j] == param->x) count++;
//         else {
//             if (count>max[param->x]) max[param->x] = count;
//             if (count<min[param->x]) min[param->x] = count;
//             count = 1;
//             param->x = new_data[j];
//         }
//     }
//     int pause_letter = 2*min[0]-1;
//     int pause_word = max[0] - min[0];
//     int dash = (max[1]+min[1])/2;

//     param->x = new_data[0];
//     count = 0;

//     for (int j = 0; j<param->new_data_count; j++) {
//         if (new_data[j] == param->x) count++;
//         else {
//             if (param->x==1){
//                 if (count>dash){
//                     printf("-");
//                 }
//                 else{
//                     printf(".");
//                 }
//             }
//             else{
//                 if (count>pause_letter){
//                     //new word
//                     printf(" ");
//                 }
//                 if (count>pause_word){
//                     // new sentence
//                     printf(" \n");
//                 }
//             }
//             count = 1;
//             param->x =  new_data[j];
//         }
//     }
// }



void wav_to_morse(struct ConversionParameters param, struct WavHeader head)
{
    int new_data[param.new_data_count];
    
    // converts samples to 0, 1
    for (int j = 0; j<param.new_data_count; j++) {
        int sum=0;
        for (int i = 0; i < param.samples_group; i++) {
            fread(&param.x, head.bytes_by_capture, 1, param.file);
            if (param.x > 0) sum += param.x;
            else sum -= param.x;
        }
        if (sum>param.samples_group*50) new_data[j] = 1;
        else new_data[j] = 0;
    }

    // detecting minimal sequence of 0 (for letter pause) and 1 (for dot)
    // maximum sequence of 1 (for dash)
    int min[2];
    int max[2];
    param.x = new_data[0];
    int count = 0;
    for (int j = 0; j<param.new_data_count; j++) {
        if (new_data[j] == param.x) count++;
        else {
            if (count>max[param.x]) max[param.x] = count;
            if (count<min[param.x]) min[param.x] = count;
            count = 1;
            param.x = new_data[j];
        }
    }
    int pause_letter = 2*min[0]-1;
    int pause_word = max[0] - min[0];
    int dash = (max[1]+min[1])/2;

    param.x = new_data[0];
    count = 0;

    for (int j = 0; j<param.new_data_count; j++) {
        if (new_data[j] == param.x) count++;
        else {
            if (param. x==1){
                if (count>dash){
                    printf("-");
                }
                else{
                    printf(".");
                }
            }
            else{
                if (count>pause_letter){
                    //new word
                    printf(" ");
                }
                if (count>pause_word){
                    // new sentence
                    printf(" \n");
                }
            }
            count = 1;
            param.x =  new_data[j];
        }
    }
}


