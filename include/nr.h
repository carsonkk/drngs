#ifndef NR_H
#define NR_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void nr_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t nr_gen();
double nr_rand();

uint32_t nr_s;
uint32_t nr_p;
uint32_t nr_q;
uint32_t nr_l;

#endif
