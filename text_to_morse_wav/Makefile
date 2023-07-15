CC			= gcc
files       = text_to_morse.c text_to_morse.h wavfile.c wavfile.h
build_dir 	= build
target	  	= $(build_dir)/text_to_morse

.PHONY : all clean

all : $(target) 

$(target) : $(files) | $(build_dir)
	$(CC) -o $@ $< -lm

$(build_dir) : 
	mkdir -p $(build_dir)

clean :
	rm -rf $(build_dir)