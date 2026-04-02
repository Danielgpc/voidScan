#pragma once
#include <stdint.h>

// Basic types for the engine
typedef int32_t fixed_t;    // Fixed point number

// Simple helpers so you don't have to write casts everywhere
#define FIXED_FROM_INT(x)   ((fixed_t)(x) << 16)
#define INT_FROM_FIXED(x)   ((x) >> 16)

// Quick multiply (safe enough for early tests)
#define FIXED_MUL(a, b)     ((fixed_t)(((int64_t)(a) * (b)) >> 16))