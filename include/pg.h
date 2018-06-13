#ifndef PG_H
#define PG_H

#include <stdint.h>
#include <math.h>

#include "helper.h"

void pg_init(uint32_t, uint32_t);
uint32_t pg_gen();
double pg_rand();

uint32_t pg_s;
uint32_t pg_l;

#endif
