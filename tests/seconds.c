#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "lcg.h"
#include "bbs.h"
#include "rsa.h"
#include "msrsa.h"
#include "rab.h"
#include "pg.h"
#include "nr.h"

static void timed(uint32_t, uint32_t *, uint32_t **, uint32_t **);

int main(int argc, char *argv[]) {
  uint32_t lcg_ansi[3] = {1103515245, 12345, 0x80000000};
  uint32_t p = 2017;
  uint32_t q = 1153;
  uint32_t l = 32;
  uint32_t i = 0;
  uint32_t j = 0;
  uint32_t *sec, *msec;
  time_t seed = time(NULL);

  sec = malloc(28*sizeof(uint32_t));
  msec = malloc(28*sizeof(uint32_t));

  lcg_init(seed, lcg_ansi[0], lcg_ansi[1], lcg_ansi[2]);
  bbs_init(seed, p, q, l);
  rsa_init(seed, p, q, l);
  msrsa_init(seed, p, q, l);
  rab_init(seed, p, q, l);
  pg_init(seed, l);
  nr_init(seed, p, q, l);

  timed(10, &i, &sec, &msec);
  for(; j < i; j++) {
    fprintf(stdout, "%us %ums\n", sec[j], msec[j]);
  }

  timed(25, &i, &sec, &msec);
  for(; j < i; j++) {
    fprintf(stdout, "%us %ums\n", sec[j], msec[j]);
  }

  timed(100, &i, &sec, &msec);
  for(; j < i; j++) {
    fprintf(stdout, "%us %ums\n", sec[j], msec[j]);
  }

  timed(250, &i, &sec, &msec);
  for(; j < i; j++) {
    fprintf(stdout, "%us %ums\n", sec[j], msec[j]);
  }

  free(sec);
  free(msec);

  return 0;
}

static void timed(uint32_t amt, uint32_t *idx, uint32_t **sec, uint32_t **msec) {
  uint32_t i;
  clock_t start, diff;

  start = clock();
  for(i = 0; i < amt; i++) {
    lcg_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    bbs_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    rsa_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    msrsa_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    rab_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    pg_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;

  start = clock();
  for(i = 0; i < amt; i++) {
    nr_rand();
  }
  diff = clock() - start;
  (*sec)[*idx] = (uint32_t)((long double)diff / CLOCKS_PER_SEC);
  (*msec)[*idx] = (uint32_t)((((long double)diff * 1000.0) / CLOCKS_PER_SEC)) % 1000;
  *idx += 1;
}