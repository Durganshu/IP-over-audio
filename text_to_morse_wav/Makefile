CC = gcc
CFLAGS = -Wall -Wextra
SRCS       = main.c morse_core.c text_to_morse.c text_to_morse.h wavfile.c wavfile.h
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
	rm -rf $(build_dir) *.o