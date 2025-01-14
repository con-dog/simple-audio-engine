# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fpack-struct

# Get all .c files in current directory
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Main target
TARGET = main

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $@ with objects: $^"
	$(CC) $^ $(LIBS) -o $@

# General rule for object files
%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Specific rule for main.o
main.o: main.c
	@echo "Compiling main.c"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning project..."
	rm -f $(TARGET) $(OBJ) main.o
	find . -type f -name "*.o" -delete
	find . -type f -name "*.so" -delete
	find . -type f -name "*.a" -delete
	find . -type f -name "*.d" -delete
	find . -type f -name "*.gch" -delete

rebuild: clean all

.PHONY: all clean rebuild