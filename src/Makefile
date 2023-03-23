CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99
SOURCES = APIG23.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
