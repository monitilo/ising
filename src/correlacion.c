#include "correlacion.h"
#include <stdio.h>

int autocorr(float *vector, int niter, float *rho ){
  float denom=0,num=0, mu ;

  mu=esperanza(vector, niter);

  for(int i=0;i<niter;i++) denom = denom + (vector[i]-mu) *(vector[i] - mu);

  for(int i=0;i<niter;i++) {
    num=0;
    for(int k=0;k<niter-i;k++) num = num + (vector[k]-mu)*(vector[k+i]-mu);
    rho[i] = num/denom ;
  }

  return 0 ;
}
float esperanza(float *vector, int n) {
  float mu=0;

  for(int i=0;i<n;i++) mu = mu + vector[i];
  mu = mu/n ;

  return mu ;
}
