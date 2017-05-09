#include "metropolis.h"
#include "stdlib.h"
#include <math.h>

int metropolis(int *lattice, int n, float T) {

  int idx,e;

  idx = pick_site(lattice,n);
  e = flip(lattice,n,T,idx);

  return e;
}

int pick_site(int *lattice, int n) {
  int i;
  i = rand() % (n*n-1);
  return i;
}

int flip(int *lattice, int n, float T, int idx) {

  int e0, e, deltae;
  float pi;

  e0 = energia(lattice,n);
  lattice[idx]=lattice[idx]*(-1);
  e = energia(lattice,n)
  deltae = e - e0;

  pi = exp(-deltae/T);

  if(pi<=1){
    if( pi < ((float)rand() / (float)RAND_MAX) ){
      lattice[idx]=lattice[idx]*(-1);
      e=e0;
    }
  }
  
  return e;
}

int energia(int *lattice, int n){

  int i,j,e;

  //primera fila (i=0)
  //el (0,0)
  e = lattice[0]*(lattice[1]+lattice[n]+lattice[n-1]+lattice[(n-1)*n]);
  //el (0,n-1)
  e = e + lattice[n-1]*(lattice[0]+lattice[(n-1)*n+n-1]+lattice[n-2]+lattice[n-1+n]);
  //el (n-1,0)
  e = e + lattice[(n-1)*n]*(lattice[(n-1)*n+1]+lattice[(n-1)*n-n]+lattice[0]+lattice[(n-1)*n+n-1]);
  //el (n-1,n-1)
  e = e + lattice[(n-1)*n+n-1]*(lattice[(n-1)*n+n-2]+lattice[(n-1)*n-1]+lattice[n-1]+lattice[n*(n-1)]);

  for(j=1;j<n-2;j++){

    //i=0
    e = e + lattice[j]*(lattice[j-1]+lattice[j+1]+lattice[j+n]+lattice[j+n*(n-1)]);
    //i=n-1
    e = e + lattice[j+n*(n-1)]*(lattice[j+n*(n-1)-n]+lattice[j]+lattice[j+n*(n-1)+1]+lattice[j+n*(n-1)-1]);
    i = j;
    //j=0
    e = e + lattice[i*n]*(lattice[i*n+1]+lattice[i*n+n]+lattice[i*n-n]+lattice[i*n+n-1]);
    //j=n-1
    e = e + lattice[i*n+n-1](lattice[i*n]+lattice[i*n+n-2]+lattice[i*n+n-1+n]+lattice[i*n-1]);

  }

  for(i=1;i<n-1;i++){

    for(j=1;j<n-1;j++) e = e + lattice[i*n+j]*(lattice[i*n+j+1]+lattice[i*n+j-1]+lattice[(i+1)*n+j]+lattice[(i-1)*n+j]);

  return e;

}
