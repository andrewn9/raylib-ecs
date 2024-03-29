# Directories
SRC_DIR = ./src
INC_DIR = ./include
LIB_DIR = ./lib
EXE_DIR = .
EXE_NAME = game

# Compiler and flags
CC = g++
CFLAGS = -O2 -Wall -Wno-missing-braces -I$(INC_DIR)

# Linker and flags
LDFLAGS = -L$(LIB_DIR) -lraylib -lGL -lX11 -lm -lpthread

# Source files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Output executable
EXE = $(EXE_DIR)/$(EXE_NAME)

.PHONY: all clean

all: clean $(EXE)

$(EXE): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXE)
