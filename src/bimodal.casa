#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include <math.h>
#include "lattice.h"
#include "correlacion.h"

int main(int argc, char **argv) {

  int n = 32;
  float prob = 1;
  float T = 2.30;
  int niter = n*n*5;
  float J=1, B=0;
  float e ;
  int m;
  FILE *fs;
  int qiter = 10000;


  srand(time(NULL));

  int *lattice = malloc(n * n * sizeof(int));

  fill_lattice(lattice, n, prob);

  fs = fopen ("bimodal.txt", "a");
  fprintf(fs,"#T=%f J=%f B=%f niter=%d qiter=%d\n",T,J,B,niter,qiter);
  fprintf(fs,"#evector mvector \n");
  fclose(fs);

  for (int w=0 ; w<1 ; w++){


    printf("L = %d; T = %f; LargoCadena = %d, Promedio = %d\n",n,T,niter,qiter);

    float *evector = malloc(qiter*sizeof(float));
    float *mvector = malloc(qiter*sizeof(float));
    float sigmaE = 0;
    float sigmaM = 0;

    float *expo = malloc(10*sizeof(float));

    for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
    for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;

    e = energia(lattice,n,J,B);
    m = magnetizacion(lattice,n);

    for (int i = 0; i < n*n*n; i++) metropolis(lattice, n, J, B, expo, &e, &m);


    for (int q=0; q<qiter;q++){


      for (int i = 0; i < niter; i++) metropolis(lattice, n, J, B, expo, &e, &m);

      evector[q] = e;
      mvector[q] = ((float) m );
      fs = fopen ("bimodal.txt", "a");
      fprintf(fs,"%f %f \n" , evector[q],  mvector[q]);
      fclose(fs);


    }

    free (evector);
    free(mvector);

    free(expo);

  }

  free(lattice);

  return 0;

}
