# CC = gcc
# CFLAGS = -Wall -Wextra
# LINK_TARGET = test_morse

# OBJS = \
# 	test_morse.o morse_base.o morse_decoder.o morse_encoder.o \

# REBUILDABLES = $(OBJS) $(LINK_TARGET) 

# all : $(LINK_TARGET)

# clean: 
# 	rm -f $(REBUILDABLES)


# % : %.o
# 	$(CC) $(CFLAGS) -o  $@ $^ 
  

# %.o : %.c
# 	$(CC) $(CFLAGS) -o $@ -c $<
  
# morse_base.o : morse_base.h
# morse_decoder.o : morse_decoder.h
# morse_encoder.o : morse_encoder.h

# CC = gcc
# CFLAGS = -Wall -Wextra
# TARGET = test_morse
# SRCS = test_morse.c morse_base.c morse_decoder.c morse_encoder.c 
# OBJS = $(SRCS:.c=.o)
# # OBJS = test_morse.o morse_base.o morse_decoder.o morse_encoder.o \
# # 	real_morse.o
		
# .PHONY: all clean

# all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAGS = -pg -g -Wall -Wextra
TARGET = test_morse real_morse
SRCS = test_morse.c morse_base.c morse_decoder.c morse_encoder.c real_morse.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

test_morse: test_morse.o morse_base.o morse_decoder.o morse_encoder.o
	$(CC) $(CFLAGS) $^ -o $@

real_morse: real_morse.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
