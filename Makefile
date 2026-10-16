CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

TARGET = apc
SOURCES = main.c apc.c add.c sub.c mul.c div.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe

rebuild: clean all
