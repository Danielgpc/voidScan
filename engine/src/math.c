#include "math.h"

fixed_t addAngle(fixed_t angle, fixed_t add) {
  if (angle + add > INT_FROM_FIXED(360)) {
      return angle + add - INT_FROM_FIXED(360);
    } else {
      return angle + add;
    }
}