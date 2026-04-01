#include <engine.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  
  // Create an initialize renderer
  Renderer renderer = {0};

  if (!initRenderer(&renderer)) {
    printf("Failed to initialize renderer\n");
    return 1;
  }

  // Init input
  InputState input = {0};
  initInput(&input);

  // Create player
  Player player = {0};

  int quit = 0;
  SDL_Event event;

  while (!input.quit) {
    updateInput(&input);        // <-- call this first every frame

    // Clear framebuffer to dark retro color
    SDL_FillRect(renderer.framebuffer, NULL,
        SDL_MapRGB(renderer.framebuffer->format, 20, 20, 40));

    // TODO: raycasting will go here later

    handleInput(&input);

    renderPresent(&renderer);
  }

  shutdownRenderer(&renderer);
  return 0;
}
