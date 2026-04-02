#include "math.h"

fixed_t addAngle(fixed_t angle, fixed_t add) {
  // Get the raw fixed-point representation of 360
  fixed_t fullCircle = FIXED_FROM_INT(360); 
  
  // Perform the addition
  fixed_t result = angle + add;

  // Modulo works on the raw underlying bits
  result %= fullCircle;

  // Handle negative wrap-around
  if (result < 0) {
    result += fullCircle;
  }

  return result;
}