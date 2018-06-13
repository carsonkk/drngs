#ifndef BBS_H
#define BBS_H

#include <stdint.h>

#include "helper.h"

void bbs_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t bbs_gen();
double bbs_rand();

uint32_t bbs_s;
uint32_t bbs_p;
uint32_t bbs_q;
uint32_t bbs_l;

#endif
