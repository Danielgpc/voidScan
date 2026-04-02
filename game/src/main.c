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

    for(int x = 0; x < renderer.width; x++) {
      
      // 1. Calculate ray angle for this column
      fixed_t ray_angle = addAngle(player.angle, FIXED_FROM_INT(x - renderer.width/2) / 8);
      
      // 2. Very simple ray marching (step forward until we hit a wall)
      fixed_t ray_x = player.x;
      fixed_t ray_y = player.y;
      fixed_t distance = FIXED_FROM_INT(0);
      
      // March forward in small steps
      for(int step = 0; step < 200; step++) {           // max 200 steps to avoid infinite loop
        distance += FIXED_FROM_INT(1);                // move 1 unit forward each step
        
        ray_x = player.x + FIXED_MUL(distance, fixed_cos(ray_angle));
        ray_y = player.y + FIXED_MUL(distance, fixed_sin(ray_angle));
        
        // Convert to map grid coordinates
        int map_x = INT_FROM_FIXED(ray_x);
        int map_y = INT_FROM_FIXED(ray_y);
        
        // Check if we hit a wall
        if (map_x < 0 || map_x >= 16 || map_y < 0 || map_y >= 16) break;
        if (MAP[map_y][map_x] == 1) {
          break;   // we hit a wall!
        }
      }
      
      // 3. Use the distance we found
      int wall_height = 400 / (INT_FROM_FIXED(distance) + 1);   // +1 to avoid divide by zero
      if (wall_height < 4) wall_height = 4;
      
      int draw_start = (S_HEIGHT - wall_height) / 2;
      if (draw_start < 0) draw_start = 0;
      
      SDL_Rect slice = { x, draw_start, 1, wall_height };
      
      Uint32 color;
      if (x < renderer.width / 2) {
        color = SDL_MapRGB(renderer.framebuffer->format, 120, 120, 255);
      } else {
        color = SDL_MapRGB(renderer.framebuffer->format, 70, 70, 180);
      }
      
      SDL_FillRect(renderer.framebuffer, &slice, color);
    }

    printf("%i", player.angle);

    handleInput(&input, &player);

    renderPresent(&renderer);
  }

  shutdownRenderer(&renderer);
  return 0;
}
