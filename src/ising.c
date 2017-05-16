#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {

  int n = 8;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 2.0;
  int niter = 10000;
  FILE *fs;

  if(argc==4){

    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%d",&niter);

  }

  int *de = malloc(niter*sizeof(int));

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  printf("L = %d; T = %f; Z = %d\n",n,T,niter);


  for (int i = 0; i < niter; i++) {

    de[i] = metropolis(lattice, n, T);

  }

  fs = fopen("de.txt","a");
  for(int i = 0;i < niter; i++) fprintf(fs,"%d\n",de[i]);
  fclose(fs);

  print_lattice(lattice,n);

  free(lattice);
  return 0;
}
