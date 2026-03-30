# Engine Makefile

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

# Directory for object files and library
OBJDIR = ../build/engine

# Source files
SRCS = renderer.c

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Library name
LIB = $(OBJDIR)/libengine.a

all: $(LIB)

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean