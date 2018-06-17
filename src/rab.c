#include "rab.h"

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void rab_init(uint32_t s, uint32_t p, uint32_t q, uint32_t l) {
  rab_s = s;
  rab_p = p;
  rab_q = q;
  rab_l = l;
}

/*
  Generate a new raw value
*/
uint32_t rab_gen() {
  uint32_t n = rab_p * rab_q;
  uint32_t r = rab_s % (n - 1);
  uint32_t rg, i, x_in, x_out;

  do {
    if(++r == n) {
      r = 1;
    }
    rg = gcd(r, n);
  } while(rg != 1);
  x_in = r;
  for(i = 0; i < rab_l; i++) {
    x_in = (x_in * x_in) % n;
    if(x_in >= n / 2) {
      x_in = n - x_in;
    }
    x_out <<= 1;
    x_out |= x_in % 2;
  }
  rab_s = x_out;

  return x_out;
}

/*
  Generate a new random value [0.0, 1.0)
*/
double rab_rand() {
  return ((rab_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}
