# Game Makefile

# Detect OS
UNAME := $(shell uname)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -D_THREAD_SAFE -I../engine
LDFLAGS = -lSDL2 ../build/engine/libengine.a

# OS-specific paths
ifeq ($(UNAME), Darwin)
	CFLAGS += -I/opt/homebrew/include -I/opt/homebrew/include/SDL2
	LDFLAGS += -L/opt/homebrew/lib
endif

# Directory for object files and executable
OBJDIR = ../build/game

# Source files
SRCS = main.c

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Executable name
TARGET = $(OBJDIR)/voidscan

all: $(TARGET)

$(TARGET): $(OBJS) ../build/engine/libengine.a
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run