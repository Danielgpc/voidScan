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
  Player player = {
    .x = FIXED_FROM_INT(8),
    .y = FIXED_FROM_INT(10),
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

    // Get the sart and end angle for raycasting
    fixed_t start = addAngle(player.angle, -90);
    fixed_t end = addAngle(player.angle, INT_FROM_FIXED(90));

    fixed_t step_size = (INT_FROM_FIXED(end) - INT_FROM_FIXED(start)) / (renderer.width - 1);

    for (int x = 0; x < renderer.width; x++)
    {
      fixed_t j = start + (FIXED_MUL(FIXED_FROM_INT(x), step_size));
      // printf("%i", INT_FROM_FIXED(j));
    }

    printf("%i", player.angle);

    handleInput(&input, &player);

    renderPresent(&renderer);
  }

  shutdownRenderer(&renderer);
  return 0;
}
