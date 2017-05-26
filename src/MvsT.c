#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include <math.h>
#include "lattice.h"
#include "correlacion.h"

int main(int argc, char **argv) {

  int n = 20;
  float prob = 0.5;
  float T = 0;
  int niter = 500000;
  float J=1, B=0;
  float e ;
  int m;
  FILE *fs;

  srand(time(NULL));

  for (int w=0 ; w<100 ; w++){

    T = 0.04 *(w+1) ;

    printf("L = %d; T = %f; Z = %d\n",n,T,niter);


    int *lattice = malloc(n * n * sizeof(int));


    fill_lattice(lattice, n, prob);

    float *expo = malloc(10*sizeof(float));

    for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
    for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;


    e = energia(lattice,n,J,B);
    m = magnetizacion(lattice,n);


    for (int i = 0; i < niter; i++) metropolis(lattice, n, J, B, expo, &e, &m);



    fs= fopen ("MvsT.txt", "a");
    fprintf(fs,"%f %f %d\n" , T, e, m);
    fclose(fs);

    free(lattice);
    free(expo);

  }
  return 0;
}
