#include <stdio.h>
#include <time.h>

#include "brand.h"

int main(int argc, char *argv[]) {
  int i;
  int slots[20];

  srand(time(NULL));
  bsetx(20);
  for(i = 0; i < 20; i++) {
    slots[i] = 0;
  }

  for(i = 0; i < 1000000; i++) {
    slots[brand()]++;
  }
  fprintf(stdout, "brand\n");
  for(i = 0; i < 20; i++) {
    fprintf(stdout, "%d: %%%f\n", i, (((double)slots[i]/1000000)*100.0));
  }

  return 0;
}
