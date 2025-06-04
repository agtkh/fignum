CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = fignum
SRCS = fignum.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

