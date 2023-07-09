CC = gcc
CFLAGS = -Wall -Wextra
TARGET = test_morse
SRCS = test_morse.c morse_base.c morse_decoder.c morse_encoder.c 
OBJS = $(SRCS:.c=.o)
# OBJS = test_morse.o morse_base.o morse_decoder.o morse_encoder.o \
# 	real_morse.o
		
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# CC = gcc
# CFLAGS = -pg -g -Wall -Wextra
# TARGET = test_morse real_morse
# SRCS = test_morse.c morse_base.c morse_decoder.c morse_encoder.c real_morse.c
# OBJS = $(SRCS:.c=.o)

# .PHONY: all clean

# all: $(TARGET)

# test_morse: test_morse.o morse_base.o morse_decoder.o morse_encoder.o
# 	$(CC) $(CFLAGS) $^ -o $@

# real_morse: real_morse.c
# 	$(CC) $(CFLAGS) $< -o $@

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)
