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
  int niter = n*n*5;
  float J,B;
  float e ;
  int m;
  FILE *fs;
  int qiter = 100;
  char name[100];

  srand(time(NULL));

  float B_vector[5]={0,0.001,0.01,0.1,1};
  float J_vector[6]={-1,-0.5,-0.1,0.1,0.5,1};
  float Tmax_vector[5]={5,5,5,20,200};
  float Tmax, pendiente;
  int wmax = 5000;
  float *expo = malloc(10*sizeof(float));
  int *lattice = malloc(n * n * sizeof(int));


  for(int b=0;b<5;b++){

    fill_lattice(lattice, n, prob);

    B = B_vector[b];
    Tmax = Tmax_vector[b];
    pendiente = Tmax/wmax;

    for(int j=0;j<6;j++){

      J = J_vector[j];

      sprintf(name, "data_2e_J%f_B%f.txt", J,B);
      fs = fopen (name, "a");
      fprintf(fs,"# J=%f B=%f niter=%d qiter=%d\n",J,B,niter,qiter);
      fprintf(fs,"# T eMean sigmaE mMean sigmaM \n");
      fclose(fs);

      for (int w=0 ; w<wmax ; w++){

        T = Tmax - pendiente * (w+1) ;

        printf("L = %d; T = %f; B = %f; J = %f, Promedio = %d\n",n,T,B,J,qiter);

        float eMean = 0;
        float mMean = 0;
        float sigmaE = 0;
        float sigmaM = 0;

        for (int i=-2; i<3; i++) expo[i+2]  = exp(-(J*4*i+B)/T) ;
        for (int i=-2; i<3; i++) expo[i+2+5]= exp(-(J*4*i-B)/T) ;

        e = energia(lattice,n,J,B);
        m = magnetizacion(lattice,n);

        for (int q=0; q<qiter;q++){

          for (int i = 0; i < niter; i++) metropolis2(lattice, n, J, B, expo, &e, &m);

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

  }

  free(lattice);
  free(expo);
  return 0;

}
