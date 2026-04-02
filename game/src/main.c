#include <engine.h>
#include <SDL2/SDL.h>
#include <stdio.h>

// MAP
const int MAP[16][16] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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
  Player player = {
    .x = FIXED_FROM_INT(2),
    .y = FIXED_FROM_INT(2),
    .z = FIXED_FROM_INT(0),
    .angle = FIXED_FROM_INT(0),
    .speed = FIXED_FROM_INT(0)
  };

  int quit = 0;
  SDL_Event event;

  while (!input.quit) {
    updateInput(&input);        // <-- call this first every frame

    // Clear framebuffer to dark retro color
    SDL_FillRect(renderer.framebuffer, NULL, SDL_MapRGB(renderer.framebuffer->format, 20, 20, 40));

    raycast(&player, &renderer);

    handleInput(&input, &player);

    renderPresent(&renderer);
  }

  shutdownRenderer(&renderer);
  return 0;
}
