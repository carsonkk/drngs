#include "rsa.h"

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void rsa_init(uint32_t s, uint32_t p, uint32_t q, uint32_t l) {
  rsa_s = s;
  rsa_p = p;
  rsa_q = q;
  rsa_l = l;
}

/*
  Generate a new raw value
*/
uint32_t rsa_gen() {
  uint32_t n = rsa_p * rsa_q;
  uint32_t t = (rsa_p - 1) * (rsa_q - 1);
  uint32_t e = (rsa_s % (t - 2)) + 1;
  uint32_t r = (rsa_s % (n - 1)) + 1;
  uint32_t x_out = 0;
  uint32_t eg, i, j, x_in;

  do {
    if(++e == t - 1) {
      e = 2;
    }
    eg = gcd(e, t);
  } while(eg != 1);
  for(i = 0; i < rsa_l; i++) {
    x_in = 1;
    for(j = 0; j < e; j++) {
      x_in = (x_in * r) % n;
    }
    r = x_in;
    x_out <<= 1;
    x_out |= r % 2;
  }
  rsa_s = x_out;

  return x_out;
}

/*
  Generate a new double value [0.0, 1.0)
*/
double rsa_rand() {
  return ((rsa_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}

/*
https://simple.wikipedia.org/wiki/RSA_algorithm
*/