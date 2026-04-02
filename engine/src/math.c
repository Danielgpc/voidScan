#include "math.h"

/**
 * Adds a given angle to a player's current angle.
 *
 * Handles wrapping around 360 degrees (both positive and negative).
 *
 * @param angle The current angle of the player.
 * @param add The angle to add to the player's current angle.
 * @return The resulting angle after addition and wrapping.
 */
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

/**
 * Returns the sine of a given angle in fixed-point format.
 *
 * @param angle The angle in fixed-point format.
 * @return The sine of the given angle.
 */
fixed_t fixed_sin(fixed_t angle) {

}

/**
 * Returns the cosine of a given angle in fixed-point format.
 *
 * @param angle The angle in fixed-point format.
 * @return The cosine of the given angle.
 */
fixed_t fixed_cos(fixed_t angle) {
  
}