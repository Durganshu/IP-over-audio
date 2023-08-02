#include <stdio.h>
#include <string.h>
#include <sndfile.h>
#include <fftw3.h>

#define BUFFER_SIZE 1024

int read_audio(const char* filename, double** pcm_data, int* num_samples, int* sample_rate) {
    SNDFILE* sndfile;
    SF_INFO sfinfo;

    // Open the audio file
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile) {
        printf("Error opening the audio file '%s'\n", filename);
        return -1;
    }

    // Check if the file is in the supported format (e.g., WAV, FLAC, etc.)
    if ((sfinfo.format & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
        printf("Unsupported audio format.\n");
        sf_close(sndfile);
        return -1;
    }

    // Allocate memory to store PCM data
    int num_channels = sfinfo.channels;
    int num_frames = sfinfo.frames;
    int data_size = num_frames * num_channels;
    *pcm_data = (double*)malloc(sizeof(double) * data_size);

    // Read audio data into the buffer
    int read_count = sf_read_double(sndfile, *pcm_data, data_size);

    // Clean up and return
    sf_close(sndfile);

    *num_samples = read_count / num_channels;
    *sample_rate = sfinfo.samplerate;

    return 0;
}


#define THRESHOLD 0.5 // Adjust this threshold according to your audio

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


int main() {
    double* pcm_data;
    int num_samples, sample_rate;

    // Read audio file
    const char* filename = "path/to/your/audio/file.wav";
    if (read_audio(filename, &pcm_data, &num_samples, &sample_rate) != 0) {
        return 1;
    }

    // Detect Morse code pulses or tones
    detect_morse(pcm_data, num_samples);

    // Decode Morse code into text
    // You need to implement the decoding function (decode_morse) to complete this step

    // Free allocated memory
    free(pcm_data);

    return 0;
}





	
int main() {
	char name[50];
	char output[200];
	printf("Enter your name, please: ");
	fgets(name, 50, stdin);
	name[strcspn(name, "\n")] = '\0';
	fancy_hello(name, output);
	return 0;
	}