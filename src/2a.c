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
  int niter = n*n*5;
  float J=0,B;
  float e ;
  int m;
  FILE *fs;
  int qiter = 200;
  char name[100];


  srand(time(NULL));

  float B_vector[5]={0.001,0.01,0.1,1,10};
  float Tmax_vector[5]={0.5,5,20,200,3000};
  float Tmax, pendiente;
  int wmax=5000;

  for(int j=0;j<5;j++){

    int *lattice = malloc(n * n * sizeof(int));

    fill_lattice(lattice, n, prob);

    B = B_vector[j];
    Tmax = Tmax_vector[j];
    pendiente = Tmax/wmax;

    sprintf(name, "data_2a_B%f.txt", B);
    fs = fopen (name, "a");
    fprintf(fs,"#J=%f B=%f niter=%d qiter=%d\n",J,B,niter,qiter);
    fprintf(fs,"#T eMean sigmaE mMean sigmaM \n");
    fclose(fs);

    for (int w=0 ; w<wmax ; w++){

      T = Tmax - pendiente * (w+1) ;

      printf("L = %d; T = %f; B = %f; LargoCadena = %d, Promedio = %d\n",n,T,B,niter,qiter);

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

      free(expo);

    }

    free(lattice);

  }
  return 0;

}
