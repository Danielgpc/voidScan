#include "renderer.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  Renderer renderer = {0};

  if (!initRenderer(&renderer)) {
    printf("Failed to initialize renderer\n");
    return 1;
  }

  int quit = 0;
  SDL_Event event;

  while (!quit) {
    // Event handling
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
      // TODO: Add keyboard input for movement later
    }

    // === DRAWING STARTS HERE (CPU side) ===
    // Clear framebuffer to black (replace this with your raycaster later)
    SDL_FillRect(renderer.framebuffer, NULL,
                 SDL_MapRGB(renderer.framebuffer->format, 20, 20,
                            40)); // dark retro color

    // TODO: Here you will put your raycasting loop
    // for each column x from 0 to width-1:
    //     cast ray, find wall height, draw vertical textured column into
    //     framebuffer->pixels

    // Present the frame
    renderPresent(&renderer);
  }

  shutdownRenderer(&renderer);
  return 0;
}
