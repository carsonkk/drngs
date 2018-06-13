#ifndef RSA_H
#define RSA_H

#include <stdint.h>

#include "helper.h"

void rsa_init(uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t rsa_gen();
double rsa_rand();

uint32_t rsa_s;
uint32_t rsa_p;
uint32_t rsa_q;
uint32_t rsa_l;

#endif
