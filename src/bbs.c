#include "bbs.h"

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void bbs_init(uint32_t s, uint32_t p, uint32_t q, uint32_t l) {
  bbs_s = s;
  bbs_p = p;
  bbs_q = q;
  bbs_l = l;
}

/*
  Generate a new raw value
*/
uint32_t bbs_gen() {
  uint32_t n = bbs_p * bbs_q;
  uint32_t r = bbs_s % (n - 1);
  uint32_t rg, i, x_in, x_out;

  do {
    if(++r == n) {
      r = 1;
    }
    rg = gcd(r, n);
  } while(rg != 1);
  x_in = r;
  for(i = 0; i < bbs_l; i++) {
    x_in = (x_in * x_in) % n;
    x_out <<= 1;
    x_out |= x_in % 2;
  }
  bbs_s = x_out;

  return x_out;
}

/*
  Generate a new random value [0.0, 1.0)
*/
double bbs_rand() {
  return ((bbs_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}

/*
https://en.wikipedia.org/wiki/Blum_Blum_Shub
https://www.cs.indiana.edu/~kapadia/project2/node11.html
*/