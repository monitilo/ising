#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include "metropolis.h"
#include <math.h>
#include "lattice.h"
#include "correlacion.h"

int main(int argc, char **argv) {

  int n = 254;
  float prob = 0.5;
  float T = 0;
  int niter = n*n*5;
  float J=0, B=0;
  float e ;
  int m;
  FILE *fs;
  int qiter = 50;
  char name[100];

  srand(time(NULL));

  float *expo = malloc(10*sizeof(float));

  for (int l=0; l<1 ;l++){
    n = n + 2;
    niter = n*n*5;
    T = 1.234567 ;
    J=0;
    int *lattice = malloc(n * n * sizeof(int));

    for (int k=0; k<2 ;k++){
      J= J + 0.3;

      fill_lattice(lattice, n, prob);

      sprintf(name, "data_2c_J%f_n%d.txt", J,n);
      fs = fopen (name, "a");

      fprintf(fs,"#n=%d J=%f B=%f niter=%d qiter=%d\n",n,J,B,niter,qiter);
      fprintf(fs,"#T eMean sigmaE mMean sigmaM \n");
      fclose(fs);

      printf("L = %d; LargoCadena = %d, Promedio = %d, J= %f\n",n,niter,qiter, J);

      //printf("L = %d; T = %f; LargoCadena = %d, Promedio = %d, J= %f\n",n,T,niter,qiter, J);

      for (int w=0 ; w<500 ; w++){

        T = 3 - 0.006 *(w+1) ;

        float eMean = 0;
        float mMean = 0;
        float sigmaE = 0;
        float sigmaM = 0;


        for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+2*B)/T) ;
        for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-2*B)/T) ;

        for (int q=0; q<qiter;q++){

          e = energia(lattice,n,J,B);
          m = magnetizacion(lattice,n);

          for (int i = 0; i < niter; i++) metropolis(lattice, n, J, B, expo, &e, &m);

          eMean = e/qiter + eMean;
          mMean = ((float) m )/qiter + mMean;
          sigmaE = e*e/qiter + sigmaE;
          sigmaM = ((float) m)*((float) m)/qiter + sigmaM;

        }

        sigmaE = sigmaE - eMean*eMean;
        sigmaM = sigmaM - mMean*mMean;

        fs = fopen (name, "a");
        fprintf(fs,"%f %f %f %f %f\n" , T, eMean, sigmaE, mMean, sigmaM);
        fclose(fs);
      }
    }

    free(lattice);
  }
  free(expo);


  return 0;

}
