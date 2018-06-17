#include "nr.h"

static void vbin(uint32_t, uint32_t, uint32_t **);
static void vsum(uint32_t *, uint32_t *, uint32_t, uint32_t *);
static void iprod(uint32_t *, uint32_t *, uint32_t, uint32_t *);

/*
  Initialize the RNG
  NOTE: Only call this funtion once
*/
void nr_init(uint32_t s, uint32_t p, uint32_t q, uint32_t l) {
  nr_s = s;
  nr_p = p;
  nr_q = q;
  nr_l = l;
}

/*
  Generate a new raw value
*/
uint32_t nr_gen() {
  uint32_t n = nr_p * nr_q;
  uint32_t g = nr_s % ((uint32_t)sqrt(n) - 1);
  uint32_t k = 1;
  uint32_t k_sz = nr_p;
  uint32_t rd = nr_s % n;
  uint32_t s = nr_s;
  uint32_t *b, *d, *a, *r;
  uint32_t u, v, w, i, j, x_out;

  g *= g;
  while(k_sz >>= 1) {
    k++;
  }
  b = malloc(k*sizeof(uint32_t));
  d = malloc(2*k*sizeof(uint32_t));
  a = malloc(2*k*sizeof(uint32_t));
  r = malloc(2*k*sizeof(uint32_t));
  for(i = 0; i < 2*k; i++) {
    a[i] = s % nr_p;
    s = a[i] * a[i];
    r[2*k-i-1] = rd % 2;
    rd >>= 1;
  }
  for(i = 0; i < nr_l; i++) {
    vbin(i, k, &b);
    vsum(a, b, k, &u);
    v = 1;
    for(j = 0; j < u; j++) {
      v = (v * g) % n;
    }
    vbin(v, 2*k, &d);
    iprod(r, d, k, &w);
    x_out <<=1;
    x_out |= w;
  }
  nr_s = x_out;

  free(b);
  free(d);
  free(a);
  free(r);
  return x_out;
}

/*
  Generate a new random value [0.0, 1.0)
*/
double nr_rand() {
  return ((nr_gen() & (((1 << 30) - 1) << 16)) >> 16) / (double) ((1 << 16) - 1);
}

static void vbin(uint32_t u, uint32_t k, uint32_t **o) {
  uint32_t i;

  for(i = 0; i < k; i++) {
    (*o)[k-i-1] = u % 2;
    u >>= 1;
  }
}

static void vsum(uint32_t *a, uint32_t *b, uint32_t k, uint32_t *o) {
  uint32_t i;

  for(i = 0; i < 2*k; i++) {
    if(b[i/2] == 0) {
      *o += a[i];
    }
    else {
      *o += a[i+1];
    }
    i++;
  }
}

static void iprod(uint32_t *v, uint32_t *w, uint32_t k, uint32_t *o) {
  uint32_t i;

  for(i = 0; i < k; i++) {
    *o += v[i] * w[i];
  }
  *o %= 2;
}
