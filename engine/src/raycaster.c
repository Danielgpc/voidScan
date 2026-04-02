#include "raycaster.h"

void raycast(Player* player, Renderer* renderer) {
  for(int x = 0; x < renderer->width; x++) {
      
      // Calculate ray angle for this column
      fixed_t ray_angle = addAngle(player->angle, FIXED_FROM_INT(x - renderer->width/2) / FOV);
      
      // Very simple ray marching (step forward until we hit a wall)
      fixed_t ray_x = player->x;
      fixed_t ray_y = player->y;
      fixed_t distance = FIXED_FROM_INT(0);
      
      // March forward in small steps
      for(int step = 0; step < MAX_RAY_STEPS; step++) {           // max 200 steps to avoid infinite loop
        distance += FIXED_FROM_INT(1);                  // move 1 unit forward each step
        
        ray_x = player->x + FIXED_MUL(distance, fixed_cos(ray_angle));
        ray_y = player->y + FIXED_MUL(distance, fixed_sin(ray_angle));
        
        // Convert to map grid coordinates
        int map_x = INT_FROM_FIXED(ray_x);
        int map_y = INT_FROM_FIXED(ray_y);
        
        // Check if hit a wall
        if (map_x < 0 || map_x >= 16 || map_y < 0 || map_y >= 16) break;
        if (MAP[map_y][map_x] == 1) {
          break;   // we hit a wall!
        }
      }
      
      // Use the distance found to cauculate the wall height and start position
      int wall_height = WALL_HEIGHT_MUL / (INT_FROM_FIXED(distance) + 1);   // +1 to avoid divide by zero
      if (wall_height < 4) wall_height = 4;
      
      int draw_start = (S_HEIGHT - wall_height) / 2;
      if (draw_start < 0) draw_start = 0;
      
      // Create SDL_Rect for wall slice
      SDL_Rect slice = { x, draw_start, 1, wall_height };
      // Create SDL_Rect for floor
      SDL_Rect floor = { x, draw_start + wall_height, 1, S_HEIGHT - 1 };
      // Create SDL_Rect for ceiling
      SDL_Rect ceiling = { x, 0, 1, draw_start - 1 };
      
      // Calculate wall distance in int with max distance for coloring
      int dist = INT_FROM_FIXED(distance);
      int max_dist = MAX_DARK_DIST;
      if (dist > max_dist) dist = max_dist;

      // Draw ceiling
      
      Uint32 color = SDL_MapRGB(renderer->framebuffer->format, 69, 249, 4);
      SDL_FillRect(renderer->framebuffer, &ceiling, color);

      // Draw wall slice
      
      // Calculate brightness and color
      int brightness = 255 - (dist * BRIGHTNESS_MUL);
      if (brightness < 0) brightness = 0;
      color = SDL_MapRGB(renderer->framebuffer->format, 
                         brightness, 
                         brightness * (187 / 255), 
                         0);
      
      SDL_FillRect(renderer->framebuffer, &slice, color);

      // Draw floor
      
      color = SDL_MapRGB(renderer->framebuffer->format, 0, 85, 255);
      SDL_FillRect(renderer->framebuffer, &floor, color);
  }
}