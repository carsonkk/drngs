#include "lcg.h"

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void lcg_init(uint32_t s, uint32_t a, uint32_t b, uint32_t n) {
  lcg_s = s;
  lcg_a = a;
  lcg_b = b;
  lcg_n = n;
}

/*
  Generate a new raw value
*/
uint32_t lcg_gen() {
  lcg_s = (lcg_a * lcg_s + lcg_b) % lcg_n;

  return lcg_s;
}

/*
  Generate a new random value [0.0, 1.0)
*/
double lcg_rand() {
  return ((lcg_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}

/*
https://en.wikipedia.org/wiki/Linear_congruential_generator
*/