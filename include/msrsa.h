#ifndef MSRSA_H
#define MSRSA_H

#include <stdint.h>
#include <math.h>

#include "helper.h"

void msrsa_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t msrsa_gen();
double msrsa_rand();

uint32_t msrsa_s;
uint32_t msrsa_p;
uint32_t msrsa_q;
uint32_t msrsa_l;

#endif
