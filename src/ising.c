#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include <math.h>
#include "lattice.h"

int main(int argc, char **argv) {

  int n = 8;
  float prob = 0.5;
  float T = 2.0;
  int niter = 10000;
  float J=1, B=0;
  float e ;
  int m;
  FILE *fs;

  if(argc==4){

    sscanf(argv[1],"%d",&n);
    sscanf(argv[2],"%f",&T);
    sscanf(argv[3],"%d",&niter);

  }

  int *lattice = malloc(n * n * sizeof(int));

  srand(time(NULL));

  fill_lattice(lattice, n, prob);

  printf("L = %d; T = %f; Z = %d\n",n,T,niter);

  float *expo = malloc(10*sizeof(float));

  for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i-2*B)/T) ;
  for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i+2*B)/T) ;

  e = energia(lattice,n,J,B);
  m = magnetizacion(lattice,n);

  fs = fopen("e.txt","a");

  for (int i = 0; i < niter; i++) {

    fprintf(fs,"%f \n",e);
    metropolis(lattice, n, J, B, expo, &e, &m);

  }

  fclose(fs);

  print_lattice(lattice,n);

  free(lattice);
  free(expo);
  return 0;
}
