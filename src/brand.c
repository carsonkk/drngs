#include "brand.h"

static unsigned long brand_i(unsigned long, unsigned long);
static double        bscale_i();
static int           bindicate_i(double);

static unsigned long  bmin = 0;
static unsigned long  bmax = (unsigned long)RAND_MAX;
static unsigned long  bumax = (unsigned long)RAND_MAX;
static unsigned long  bucsz = (unsigned long)RAND_MAX;
static unsigned long  bus = 0;
static unsigned long  buc = 0;
static unsigned long *bua;
static unsigned long *bum;
static unsigned long *bub;

/*
  Set the minimum value for the range
*/
void bsetn(unsigned long nmin) {
  if(nmin < bmax) {
    bmin = nmin;
    bucsz = bmax - bmin;
  }
}

/*
  Set the maximum value for the range
*/
void bsetx(unsigned long nmax) {
  if(nmax > bmin) {
    bmax = nmax;
    bumax = bmax;
    bucsz = bmax - bmin;
  }
}

/*
  Set the minimum and maximum values for the range
*/
void bsetnx(unsigned long nmin, unsigned long nmax) {
  if(nmin < nmax) {
    bmin = nmin;
    bmax = nmax;
    bumax = bmax;
    bucsz = bmax - bmin;
  }
}

/*
  Set the cache size for the range
*/
void bsetc(unsigned long ncsz) {
  if(ncsz <= bmax-bmin) {
    bucsz = ncsz;
  }
}

/*
  Clean up dynamically allocated memory
*/
void bcln() {
  if(bus != 0) {
    free(bua);
  }
  if(buc != 0) {
    free(bum);
    free(bub);
  }
}

/*
  Generate a uniformly distributed random value on the order of [bmax, bmax)
  Range controlled by bmin and bmax, defaults to 0 and (unsigned long)RAND_MAX respectively
*/
unsigned long brand() {
  double res = (bmax - bmin) * bscale_i();
  double rn = res * rand();
  double rhi = res + rn;
  unsigned long rlo = (unsigned long)rn;

  while(1) {
    rlo++;
    if(rlo >= rhi || bindicate_i((rlo-rn)/(rhi-rn))) {
      return rlo + bmin - 1;
    }
    rn = rlo;
  }
}

/*
  Generate a uniformly distributed random value on the order of [0.0, 1.0)
  Range resolution controlled by bmin and bmax
*/
double brandd() {
  double d;

  do {
    d = (((brand() * bscale_i()) + brand()) * bscale_i() + brand()) * bscale_i();
  } while (d >= 1);
  return d;
}

/*
  Generate a stream of random values
  Use a cache over the size of the range to ensure total uniqueness
  When all values in the range have been generated, clear the cache and reset
  For a range of size N, the following apply:
  - O(N) memory used
  - O(N/2) lookup on average
  - O(1) update
*/
unsigned long brandus() {
  unsigned long i, ri, rt;

  if(bus == 0 || bumax == bmin) {
    if(bus == 0) {
      bua = malloc((bmax-bmin)*sizeof(unsigned long));
    }
    for(i = 0; i < bmax-bmin; i++) {
      bua[i] = bmin + i;
    }
    bumax = bmax;
    bus++;
  }
  ri = brand_i(bmin, bumax) - bmin;
  rt = bua[ri];
  for(i = 0; i < bumax-bmin-ri-1; i++) {
    bua[ri+i] = bua[ri+i+1];
  }
  bumax--;
  return rt;
}

/*
  Generate a stream of random values
  Use a MRU cache to ensure a level of relative uniqueness
  When the cache is full, evict LRU values
  For a range of size N with a cache size of S, the following apply:
  - O(S) memory used
  - O(S/2) lookup on average
  - O(1) update
*/
unsigned long *branduc() {
  unsigned long i, rt;

  if(buc == 0) {
    bum = malloc(bucsz*sizeof(unsigned long));
    bub = malloc(bucsz*sizeof(unsigned long));
    memset(bum, 0, bucsz);
    memset(bub, 0, bucsz);
    buc++;
  }
  rt = brand();

  i = buc/2;
  while(1) {
    if(bub[i] < rt) {
      if(bub[i+1] > rt) {
        for(j = buc; j > i; j--) {
          bub[j] =
        }
      }
      else {
        i += i/2;
      }
    }
    else if(num[i] > rt) {
      i -= i/2;
    }
  }


  bum[buc-1] = rt;

  buc++;
  return rt;
}

static unsigned long brand_i(unsigned long nmin, unsigned long nmax) {
  unsigned long bmin_o = bmin;
  unsigned long bmax_o = bmax;
  unsigned long rt;

  bmin = nmin;
  bmax = nmax;
  rt = brand();
  bmin = bmin_o;
  bmax = bmax_o;
  return rt;
}

static double bscale_i() {
  return 1.0 / (1.0 + RAND_MAX);
}

static int bindicate_i(double r) {
  double p;
  
  while(1) {
    p = rand() * bscale_i();
    if(p >= r) {
      return 0;
    }
    if(p+bscale_i() <= r) {
      return 1;
    }
    r = (r - p) * (1.0 + RAND_MAX);
  }
}