#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "morse_core.h"
#include "wav_to_morse.h"


char decode(char s[]) {
    int i, j;
	for (i=0; i<MAX_CHARS; i++){
        for (j = 1; morse_table[i][j] != ENDCODE; j++) {
            if (s[j - 1] != morse_table[i][j]) {
                break;
            }
        }
        if (morse_table[i][j] == ENDCODE && s[j - 1] == '\0') {
            return (char) morse_table[i][0];
        }
    }
    return ' ';
}


void wav_to_morse(ConversionParameters *param, WavHeader head, char message[MAX_SENTENCE_LENGTH]) {
    int new_data[param->new_data_count];
    short x;
    // converts samples to 0, 1
    for (int j = 0; j<param->new_data_count; j++) {
        int sum=0;
        for (int i = 0; i < param->samples_group; i++) {
            fread(&x, head.bytes_by_capture, 1, param->file);
            if (x > 0) sum += x;
            else sum -= x;
        }
        if (sum > param->samples_group*50) new_data[j] = 1;
        else new_data[j] = 0;
    }

    // detecting minimal sequence of 0 (for letter pause) and 1 (for dot)
    // maximum sequence of 1 (for dash)
    int min[2] = {0 ,0};
    int max[2] = {0 ,0};

    x = new_data[0];
    int count = 0;
    for (int j = 0; j < param->new_data_count; j++) {
        if (new_data[j] == x) count++;
        else {
            if (count>max[x]) max[x] = count;
            if (count<min[x] || min[x] ==0) min[x] = count;
            count = 1;
            x = new_data[j];
        }
    }
    int pause_letter = 2*min[0]-1;
    int pause_word = max[0] - min[0];
    int dash = (max[1]+min[1])/2;

    x = new_data[0];
    count = 1;
	char letter[MAX_CHAR_SEQ+1] = "";
	message = "";
    int let_idx = 0;

    for (int j = 0; j < param->new_data_count; j++) {
        if (new_data[j] == x) {
            count++;
            continue;
        }
        else if (x == 1) {
            if (count > dash) {
                strcat(letter, "-");
            }
            else {
                strcat(letter, ".");
            }
        }
        else if (count > pause_letter){
            // new morse word (text letter)
            message[let_idx++] = (char) decode(letter);
            letter[0] = '\0';
        }
        else if (count > pause_word){
            // new sentence (text word)
            message[let_idx++] = ' ';
            letter[0] = '\0';
        }
        count = 1;
        x = new_data[j];
    }
}


