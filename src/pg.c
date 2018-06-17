#include "pg.h"

static uint32_t h_prime[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
static uint32_t h_pelem[16] = {1, 2, 3, 5, 8, 11, 14, 15, 21, 27, 24, 35, 35, 34, 45, 51};

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void pg_init(uint32_t s, uint32_t l) {
  pg_s = s;
  pg_l = l;
}

/*
  Generate a new raw value
*/
uint32_t pg_gen() {
  uint32_t s = pg_s % 16;
  uint32_t r = (pg_s % (h_prime[s] - 1)) + 1;
  uint32_t i, j, x_in, x_out;

  for(i = 0; i < pg_l; i++) {
    x_in = 1;
    for(j = 0; j < r; j++) {
      x_in = (x_in * h_pelem[s]) % h_prime[s];
    }
    r = x_in;
    x_out <<= 1;
    x_out |= r % 2;
  }
  pg_s = x_out;

  return x_out;
}

/*
  Generate a new random value [0.0, 1.0)
*/
double pg_rand() {
  return ((pg_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}
