#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include "brand.h"

int main(int argc, char *argv[]) {
  unsigned long i;

  srand(time(NULL));
  bsetnx(10, 20);
  for(i = 0; i < 20; i++) {
    fprintf(stdout, "%lu, ", brandus());
  }
  fprintf(stdout, "\n");
  bcln();
  return 0;
}
