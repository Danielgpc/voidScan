#include "renderer.h"

#include <stdio.h>
#include "defines.h"

int initRenderer(Renderer *r) {
  r->width = S_WIDTH;
  r->height = S_HEIGHT;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 0;
  }

  r->window = SDL_CreateWindow(S_NAME,
                               SDL_WINDOWPOS_CENTERED, 
                               SDL_WINDOWPOS_CENTERED,
                               r->width, 
                               r->height, 
                               SDL_WINDOW_SHOWN
                              );
  if (!r->window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 0;
  }

  // Software renderer (important for retro feel)
  r->renderer = SDL_CreateRenderer(
                                   r->window, 
                                   -1, 
                                   SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC
                                  );
  if (!r->renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(r->window);
    SDL_Quit();
    return 0;
  }

  // Create the software framebuffer (this is our pixel buffer)
  r->framebuffer = SDL_CreateRGBSurface(
                                        0, 
                                        r->width, 
                                        r->height, 
                                        32, 
                                        0x00FF0000,
                                        0x0000FF00, 
                                        0x000000FF, 
                                        0xFF000000);
  if (!r->framebuffer) {
    printf("Framebuffer creation failed: %s\n", SDL_GetError());
    SDL_DestroyRenderer(r->renderer);
    SDL_DestroyWindow(r->window);
    SDL_Quit();
    return 0;
  }

  printf("Renderer initialized - %dx%d software framebuffer ready\n", r->width,
         r->height);
  return 1;
}

void renderPresent(Renderer *r) {
  // Create texture from our framebuffer surface (very fast)
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(r->renderer, r->framebuffer);
  if (texture) {
    SDL_RenderCopy(r->renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
  }

  SDL_RenderPresent(r->renderer);
}

void shutdownRenderer(Renderer *r) {
  if (r->framebuffer)
    SDL_FreeSurface(r->framebuffer);
  if (r->renderer)
    SDL_DestroyRenderer(r->renderer);
  if (r->window)
    SDL_DestroyWindow(r->window);
  SDL_Quit();
}
