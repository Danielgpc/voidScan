#include "input.h"

#include <SDL2/SDL.h>

/**
 * Initializes an InputState struct by setting all its member variables to zero.
 *
 * This is typically called once before the main loop of the game, to clear out any garbage
 * values that may have been left in the struct.
 * @param input The input state to initialize.
 */
void initInput(InputState* input) {
  input->forward = 0;
  input->backward = 0;
  input->left = 0;
  input->right = 0;
  input->fire = 0;
  input->use = 0;
  input->mouse_dx = 0;
  input->mouse_dy = 0;
  input->quit = 0;
}

/**
 * Resets all input state variables to zero, then processes all pending
 * SDL events and updates the input state accordingly.
 *
 * This function is called once per frame and should be called before updating
 * the game state.
 * @param input The input state to update.
 */
void updateInput(InputState* input) {
// Reset everything for this new frame
  input->forward = 0;
  input->backward = 0;
  input->left = 0;
  input->right = 0;
  input->fire = 0;
  input->use = 0;
  input->mouse_dx = 0;
  input->mouse_dy = 0;
  input->quit = 0;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      input->quit = 1;
    }
      else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        int pressed = (event.type == SDL_KEYDOWN);

      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:    input->forward     = pressed; break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:  input->backward    = pressed; break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:     input->left = pressed; break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:     input->right= pressed; break;
        case SDL_SCANCODE_SPACE: input->fire        = pressed; break;
        case SDL_SCANCODE_E:     input->use         = pressed; break;
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_Q:     input->quit        = pressed; break;
        default: break;
      }
    }
    else if (event.type == SDL_MOUSEMOTION) {
      input->mouse_dx += event.motion.xrel;
      input->mouse_dy += event.motion.yrel;
    }
  }
}

/**
 * Handles the input state by updating the player's state.
 *
 * Currently only handles basic movement (forward, backward, left, right)
 * and angle changes from mouse motion.
 *
 * @param input The current input state.
 * @param player The player to update.
 */
void handleInput(InputState* input, Player* player) {
  // Simple movement example
  if (input->forward)  player->x += FIXED_FROM_INT(MOVE_SPEED);
  if (input->backward) player->x -= FIXED_FROM_INT(MOVE_SPEED);
  if (input->left)     player->y -= FIXED_FROM_INT(MOVE_SPEED);
  if (input->right)    player->y += FIXED_FROM_INT(MOVE_SPEED);
  if (input->mouse_dx > 0 || input->mouse_dx < 0) player->angle = addAngle(player->angle, FIXED_FROM_INT(input->mouse_dx));
}