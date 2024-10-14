# Variables
CC = gcc
CFLAGS = -Wall -g
OBJ = main.o wordle.o bot.o ed1.o 
TARGET = programa

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
