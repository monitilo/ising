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
  float T;
  int niter = 1000000;
  float J=1, B=0;
  float e;
  int m;
  FILE *fs;
  int qiter = 10;

  srand(time(NULL));

  int *lattice = malloc(n * n * sizeof(int));

  fill_lattice(lattice, n, prob);

  fs = fopen ("MvsT.txt", "a");
  fprintf(fs,"#T eMean sigmaE mMean sigmaM \n");
  fclose(fs);

  for (int w=0 ; w<1000 ; w++){

    T = 0.004 *(w+1) ;

    printf("L = %d; T = %f; LargoCadena = %d, Promedio = %d\n",n,T,niter,qiter);

    float eMean = 0;
    float mMean = 0;
    float sigmaE = 0;
    float sigmaM = 0;

    float *expo = malloc(10*sizeof(float));

    for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
    for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;

    for (int q=0; q<qiter;q++){

      e = energia(lattice,n,J,B);
      m = magnetizacion(lattice,n);

      for (int i = 0; i < niter; i++) metropolis(lattice, n, J, B, expo, &e, &m);

      eMean = float_abs(e)/qiter + eMean;
      mMean = float_abs( (float) m )/qiter + mMean;
      sigmaE = e*e/qiter + sigmaE;
      sigmaM = ((float) m)*((float) m)/qiter + sigmaM;

    }

    sigmaE = sigmaE - eMean*eMean;
    sigmaM = sigmaM - mMean*mMean;

    fs = fopen ("MvsT.txt", "a");
    fprintf(fs,"%f %f %f %f %f\n" , T, eMean, sigmaE, mMean, sigmaM);
    fclose(fs);

    free(expo);

  }

  free(lattice);

  return 0;

}
