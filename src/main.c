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

int main(int argc, char *argv[]) {
  time_t seed = time(NULL);
  uint32_t lcg_ansi[3] = {1103515245, 12345, 0x80000000};
  uint32_t p = 2017;
  uint32_t q = 1153;
  uint32_t l = 32;

  lcg_init(seed, lcg_ansi[0], lcg_ansi[1], lcg_ansi[2]);
  bbs_init(seed, p, q, l);
  rsa_init(seed, p, q, l);
  msrsa_init(seed, p, q, l);
  rab_init(seed, p, q, l);
  pg_init(seed, l);
  nr_init(seed, p, q, l);

  fprintf(stdout, "LCG:   %.15f\n", lcg_rand());
  fprintf(stdout, "BBS:   %.15f\n", bbs_rand());
  fprintf(stdout, "RSA:   %.15f\n", rsa_rand());
  fprintf(stdout, "MSRSA: %.15f\n", msrsa_rand());
  fprintf(stdout, "RAB:   %.15f\n", rab_rand());
  fprintf(stdout, "PG:    %.15f\n", pg_rand());
  fprintf(stdout, "NR:    %.15f\n", nr_rand());

  return 0;
}
