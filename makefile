# Variables
CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = game
SRC = main.c

# Build rule
all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

# Clean rule to remove the built game
clean:
	rm -f $(TARGET)

