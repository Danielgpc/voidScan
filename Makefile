# Makefile for SDL Template

# Detect OS
UNAME := $(shell uname)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -D_THREAD_SAFE
LDFLAGS = -lSDL2

# OS-specific paths
ifeq ($(UNAME), Darwin)
	CFLAGS += -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
	LDFLAGS += -L/opt/homebrew/lib
endif

# For Linux, assume SDL2 is in standard paths (/usr/include/SDL2, /usr/lib)
# Add more OS support as needed

# Directory for object files and executable
OBJDIR = build

# Source files
SRCS = main.c renderer.c

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Executable name
TARGET = $(OBJDIR)/sdl_template

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run
