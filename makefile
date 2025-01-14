# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fpack-struct

# Directory structure
AUDIO_DIR = audio
LIB_DIR = lib
CONFIG_DIR = config

# Include paths
INCLUDES = \
				-I$(AUDIO_DIR) \
				-I$(CONFIG_DIR) \
				-I$(LIB_DIR) \



# Source files using find to recursively get all .c files
AUDIO_SRC = $(shell find $(AUDIO_DIR) -name '*.c')
CONFIG_SRC = $(shell find $(CONFIG_DIR) -name '*.c')
LIB_SRC = $(shell find $(LIB_DIR) -name '*.c')



# Debug prints
$(info =====================================)
$(info Source files found:)
$(info AUDIO_SRC = $(AUDIO_SRC))
$(info LIB_SRC = $(LIB_SRC))
$(info CONFIG_SRC = $(CONFIG_SRC))
$(info =====================================)

# All source files
SRC = \
    $(AUDIO_SRC) \
		$(CONFIG_SRC) \
		$(LIB_SRC)
$(info Combined sources: $(SRC))

# Object files
OBJ = $(SRC:.c=.o)
$(info Object files to be created: $(OBJ))

# Main target
TARGET = main

# Targets
all: $(TARGET)

$(TARGET): main.o $(OBJ)
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

rebuild: clean all

.PHONY: all clean rebuild