#ifndef LCG_H
#define LCG_H

#include <stdint.h>
#include <stdio.h>

void lcg_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t lcg_gen();
double lcg_rand();

uint32_t lcg_s;
uint32_t lcg_a;
uint32_t lcg_b;
uint32_t lcg_n;

#endif
