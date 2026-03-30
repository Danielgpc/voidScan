# Main Makefile for VOID_SCAN

# Targets
.PHONY: all engine game run clean

all: engine game

engine:
	$(MAKE) -C engine

game: engine
	$(MAKE) -C game

run: game
	$(MAKE) -C game run

clean:
	$(MAKE) -C engine clean
	$(MAKE) -C game clean
