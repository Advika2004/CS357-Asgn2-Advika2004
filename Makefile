#Builds targets for converting characters between tabs and spaces.
# CSC 357, Assignment 2

# Defines the compiler
CC = gcc

# Defines the flags for compilation
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic -g

# Name of the executable to be created
TARGET = hist

# List of source files 
SOURCES = CSVops.c main.c 
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

# Rule to compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to clean up the built files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Target to run the program
run:
	./$(TARGET) in1.txt

