#include "renderer.h"

#include <stdio.h>
#include "defines.h"

/**
 * @brief Initialize the renderer, creating an SDL window, renderer, and software framebuffer.
 * @param r Pointer to the Renderer struct to be initialized.
 * @return 1 on success, 0 on failure.
 */
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

  // Create the software framebuffer
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

  SDL_SetRelativeMouseMode(SDL_TRUE);

  printf("Renderer initialized - %dx%d software framebuffer ready\n", r->width,
         r->height);
  return 1;
}

/**
 * Present the current software framebuffer contents to the screen.
 *
 * This function will create an SDL_Texture from the current software
 * framebuffer surface, copy it to the screen, and then destroy the
 * temporary texture. This is very fast and efficient.
 *
 * @param r The renderer to present to.
 */
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

/**
 * Clean up all resources associated with a Renderer.
 *
 * This function will free all memory associated with the Renderer's
 * software framebuffer, destroy the SDL_Renderer, and destroy
 * the SDL_WINDOW. Finally, it will call SDL_Quit() to shut down
 * the SDL2 subsystems.
 *
 * @param r The Renderer to clean up.
 */
void shutdownRenderer(Renderer *r) {
  if (r->framebuffer)
    SDL_FreeSurface(r->framebuffer);
  if (r->renderer)
    SDL_DestroyRenderer(r->renderer);
  if (r->window)
    SDL_DestroyWindow(r->window);
  SDL_Quit();
}
