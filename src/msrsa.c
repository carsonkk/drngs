#include "msrsa.h"

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void msrsa_init(uint32_t s, uint32_t p, uint32_t q, uint32_t l) {
  msrsa_s = s;
  msrsa_p = p;
  msrsa_q = q;
  msrsa_l = l;
}

/*
  Generate a new raw value
*/
uint32_t msrsa_gen() {
  uint32_t n = msrsa_p * msrsa_q;
  uint32_t t = (msrsa_p - 1) * (msrsa_q - 1);
  uint32_t k = (uint32_t) (log((double)n) / log(2)) + 1;
  //uint32_t e = (msrsa_s % (k / 80));
  uint32_t e = 3;
  uint32_t r = (msrsa_s % (n - 1)) + 1;
  uint32_t x_out = 0;
  uint32_t eg, s, i, j, sz, x_in, x_sz;

  do {
    if(++e == k / 80) {
      e = 2;
    }
    eg = gcd(e, t);
  } while(eg != 1);
  s = (uint32_t) (k * (1 - 2.0 / e));
  for(i = 0; i < msrsa_l; i++) {
    x_in = 1;
    for(j = 0; j < e; j++) {
      x_in = (x_in * r) % n;
    }
    x_sz = x_in;
    sz = 0;
    while(x_sz >>= 1) {
      sz++;
    }
    r = x_in >> (sz - (k - s));
    x_out <<= s;
    x_out |= ((x_in << (32 - s)) >> (32 - s));
  }
  msrsa_s = x_out;

  return x_out;
}

/*
  Generate a new double value [0.0, 1.0)
*/
double msrsa_rand() {
  return ((msrsa_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}

/*
https://simple.wikipedia.org/wiki/RSA_algorithm
*/