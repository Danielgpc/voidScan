#pragma once
#include "fixed.h"

typedef struct {
  fixed_t x;
  fixed_t y;
  fixed_t z;

  fixed_t angle;

  fixed_t speed;

} Player;