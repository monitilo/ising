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
  float T = 0;
  int niter = 500000;
  float J=1, B=-1;
  float e ;
  int m;
  FILE *fs;
  int qiter = 20;

  srand(time(NULL));

  int *lattice = malloc(n * n * sizeof(int));

  fill_lattice(lattice, n, prob);

  for (int w=0 ; w<100 ; w++){

    T = 2.8 - 0.01 *(w+1) ;

    printf("L = %d; T = %f; Z = %d\n",n,T,niter);

    float *evector = malloc(qiter * sizeof(float));
    float *mvector = malloc(qiter * sizeof(float));

    float *expo = malloc(10*sizeof(float));

    for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
    for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;

      for (int q=0; q<qiter;q++){


      e = energia(lattice,n,J,B);
      m = magnetizacion(lattice,n);


      for (int i = 0; i < niter; i++) metropolis(lattice, n, J, B, expo, &e, &m);

      evector[q] = e;
      mvector[q] = (float) m ;

    }

    free(expo);

    fs= fopen ("MvsT.txt", "a");
    fprintf(fs,"%f %f %f\n" , T, esperanza(evector,qiter), esperanza(mvector,qiter));
    fclose(fs);

    free(evector);
    free(mvector);
  }
  free(lattice);

  return 0;
}
