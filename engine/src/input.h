#pragma once

typedef struct
{
  int forward;
  int backward;
  int right;
  int left;

  int fire;
  int use;

  int mouse_dx;
  int mouse_dy;

  int quit;
  
} InputState;

void initInput(InputState* input);
void updateInput(InputState* input);
void handleInput(InputState* input);