#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include <math.h>
#include "lattice.h"
#include "correlacion.h"

int main(int argc, char **argv) {

  int n = 32;
  float prob = 0.5;
  float T = 2.0;
  int niter = n*n*10;
  float J=1, B=0;
  float e ;
  int m;
  int nterm = 10000;
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

  for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
  for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;


  e = energia(lattice,n,J,B);
  m = magnetizacion(lattice,n);

  float *evector = malloc(niter*sizeof(float));
  float *mvector = malloc(niter*sizeof(float));
  float *rhoe = malloc (niter*sizeof(float));
  float *rhom = malloc (niter*sizeof(float));

  for (int i = 0; i < nterm; i++) {
    metropolis(lattice, n, J, B, expo, &e, &m);
  }

  for (int i = 0; i < niter; i++) {
    evector[i] = e;
    mvector[i] = (float) m;
    metropolis(lattice, n, J, B, expo, &e, &m);

  }

  autocorr(evector, niter, rhoe);
  autocorr(mvector, niter, rhom);

  fs= fopen ("rho.txt", "w");
  for (int i = 0; i < niter; i++) fprintf(fs,"%f %f %f %f\n", evector[i], mvector[i], rhoe[i], rhom[i]);
  fclose(fs);


  print_lattice(lattice,n);

  free(evector);
  free(mvector);
  free(rhoe);
  free(rhom);
  free(lattice);
  free(expo);


  return 0;
}
