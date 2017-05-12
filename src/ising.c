#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {

  int n = 32;
  int de;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 1000;

  if(argc==4){

    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%d",&niter);

  }
  printf("L = %d; T = %f; Z = %d\n",n,T,niter);
  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  //print_lattice(lattice,n);
  printf("L = %d; T = %f; Z = %d\n",n,T,niter);

  for (int i = 0; i < niter; i++) {
    de = metropolis(lattice, n, T);
  }

  print_lattice(lattice,n);
  return 0;
}
