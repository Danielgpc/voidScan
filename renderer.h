#pragma once
#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *framebuffer; // This is where we will draw everything (DOOM style)
  int width;
  int height;
} Renderer;

int initRenderer(Renderer *r);
void renderPresent(Renderer *r); // Present the framebuffer to screen
void shutdownRenderer(Renderer *r);
