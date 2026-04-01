#include "input.h"

#include "SDL2/SDL.h"

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