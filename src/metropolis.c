#include "metropolis.h"

#include "stdlib.h"
#include <math.h>
#include <stdio.h>

int metropolis(int *lattice, int n, float J, float B,float *expo, float *e, int *m) {

  int idx;
  float deltae;

  idx = pick_site(lattice,n);
  deltae = flip(lattice,n,idx,J,B,expo,&e,&m);


  return 0;

}

int pick_site(int *lattice, int n) {

  int i;
  i = (int)(((float)rand() / (float)RAND_MAX)*n*n);
  return i;

}

float flip(int *lattice, int n, int idx, float J, float B, float *expo, float *e, int *m) {

  float deltae;
  float pi;
  int indice,dm;

  deltae = 2*J*vecinos(lattice,n,idx) + 2*B*lattice[idx];
  dm=lattice[idx];

  if(deltae<0) lattice[idx]=lattice[idx]*(-1);
  else{
    indice=2*vecinos(lattice,n,idx)/4 ;

    if (lattice[idx]==1){
      pi=expo[indice+2];
    }

    else{
      pi=expo[indice+2+5];
    }
    if( ((float)rand() / (float)RAND_MAX) < pi ) lattice[idx]=lattice[idx]*(-1);

  }
  *e = *e + deltae;
  dm = lattice[idx]-dm;
  *m = *m +dm;
  return 0;
}

float energia(int *lattice, int n, float J, float B){
  int i;
  float e = 0;

  for(i=0;i<n*n;i++) e = e - J*vecinos(lattice,n,i)/2 - B*lattice[i] ;

  return e;

}
int magnetizacion(int*lattice, int n){
  int i;
  float m = 0;

  for(i=0;i<n*n;i++) m = m + lattice[i] ;
  return m ;
}

int vecinos(int *lattice, int n, int idx){
  int i=0, j=idx;

  while(j>=n){
      j = j-n;
      i = i+1;
  }
  int e;

  if(i==0){

    if(j==0) e = lattice[0]*(lattice[1]+lattice[n]+lattice[n-1]+
                lattice[(n-1)*n]);
    else if(j==(n-1)) e = lattice[n-1]*(lattice[0]+lattice[(n-1)*n+n-1]+
                        lattice[n-2]+lattice[n-1+n]);
    else e = lattice[j]*(lattice[j-1]+lattice[j+1]+lattice[j+n]+
              lattice[j+n*(n-1)]);

  }
  else if(i==(n-1)){

    if(j==0) e = lattice[(n-1)*n]*(lattice[(n-1)*n+1]+lattice[(n-1)*n-n]+
                lattice[0]+lattice[(n-1)*n+n-1]);
    else if(j==(n-1)) e = lattice[(n-1)*n+n-1]*(lattice[(n-1)*n+n-2]+
                          lattice[(n-1)*n-1]+lattice[n-1]+lattice[n*(n-1)]);
    else e = lattice[j+n*(n-1)]*(lattice[j+n*(n-1)-n]+lattice[j]+
            lattice[j+n*(n-1)+1]+lattice[j+n*(n-1)-1]);

  }
  else{

    if(j==0) e = lattice[i*n]*(lattice[i*n+1]+lattice[i*n+n]+lattice[i*n-n]+
                  lattice[i*n+n-1]);
    else if(j==(n-1)) e = lattice[i*n+n-1]*(lattice[i*n]+lattice[i*n+n-2]+
                          lattice[i*n+n-1+n]+lattice[i*n-1]);
    else e = lattice[i*n+j]*(lattice[i*n+j+1]+lattice[i*n+j-1]+
              lattice[(i+1)*n+j]+lattice[(i-1)*n+j]);

  }

return e;

}
