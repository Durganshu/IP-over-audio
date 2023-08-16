CC = gcc
CFLAGS = -Wall -Wextra
SRCS = morse_code/main.c morse_code/morse_core.c morse_code/text_to_wav.c morse_code/text_to_wav.h morse_code/wavfile.c morse_code/wavfile.h morse_code/wav_to_morse.c morse_code/wav_to_morse.h 
build_dir 	= build
target	  	= $(build_dir)/test_code
OBJS = $(SRCS:.c=.o)

.PHONY : all clean

all : $(target) 

$(target): $(OBJS) | $(build_dir)
	$(CC) $(CFLAGS) $(OBJS) -o $(target) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

$(build_dir) : 
	mkdir -p $(build_dir)

clean :
	rm -rf $(build_dir) morse_code/*.o