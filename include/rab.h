#ifndef RAB_H
#define RAB_H

#include <stdint.h>

#include "helper.h"

void rab_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t rab_gen();
double rab_rand();

uint32_t rab_s;
uint32_t rab_p;
uint32_t rab_q;
uint32_t rab_l;

#endif
