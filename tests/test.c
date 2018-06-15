#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include "brand.h"

int main(int argc, char *argv[]) {
  unsigned long i;
  unsigned long a, min = ULONG_MAX;

  srand(time(NULL));
  // for(i = 0; i < 17483640; i++) {
  //   a = brandx(4047483640);
  //   //fprintf(stdout, "%lu, ", a);
  //   //fflush(stdout);
  //   if(a < min) {
  //     min = a;
  //   }
  // }

  // fprintf(stdout, "%lu, ", min);

  // bsetnx(10, 20);
  // fprintf(stdout, "%lu\n", brand());

  bsetnx(10, 20);
  for(i = 0; i < 20; i++) {
    fprintf(stdout, "%lu, ", brandus());
  }
  bcln();
  return 0;
}
