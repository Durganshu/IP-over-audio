CC = gcc
CFLAGS = -Wall -Wextra
TARGET = test_morse
SRCS = test_morse.c morse_base.c morse_decoder.c morse_encoder.c 
OBJS = $(SRCS:.c=.o)
		
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
