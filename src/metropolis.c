#include "metropolis.h"
#include "stdlib.h"
#include <math.h>
#include <stdio.h>

int metropolis(int *lattice, int n, float T) {

  int idx,deltae;

  idx = pick_site(lattice,n);
  deltae = flip(lattice,n,T,idx);

  return deltae;

}

int pick_site(int *lattice, int n) {

  int i;
  i = rand() % (n*n-1);
  return i;

}

int flip(int *lattice, int n, float T, int idx) {

  int deltae;
  float pi;

  deltae = energiaVecinos(lattice,n,idx); //calculo las interacciones del spin de interes
  lattice[idx]=lattice[idx]*(-1); //flippeo el spin
  deltae = energiaVecinos(lattice,n,idx) - deltae; //calculo el delta con el spin flippeado

  pi = exp(-deltae/T);

  if(pi<=1){
    if( pi > ((float)rand() / (float)RAND_MAX) ){   //si la moneda es mas chica que la probabilidad, rechazo el cambio
      lattice[idx]=lattice[idx]*(-1);
      deltae = 0;
    }
  }

  return deltae;
}

int energia(int *lattice, int n){

  int i,j;
  int e = 0;

  for(i=0;i<n;i++) for(j=0;j<n;j++) e = e + vecinos(lattice,n,i,j);

  return e;

}

int vecinos(int *lattice, int n, int i, int j){

  int e;

  if(i==n) i = 0;
  if(i==-1) i = n-1;
  if(j==n) j = 0;
  if(j==-1) j = n-1;

  if(i==0){

    if(j==0) e = lattice[0]*(lattice[1]+lattice[n]+lattice[n-1]+lattice[(n-1)*n]);
    else if(j==(n-1)) e = lattice[n-1]*(lattice[0]+lattice[(n-1)*n+n-1]+lattice[n-2]+lattice[n-1+n]);
    else e = lattice[j]*(lattice[j-1]+lattice[j+1]+lattice[j+n]+lattice[j+n*(n-1)]);

  }
  else if(i==(n-1)){

    if(j==0) e = lattice[(n-1)*n]*(lattice[(n-1)*n+1]+lattice[(n-1)*n-n]+lattice[0]+lattice[(n-1)*n+n-1]);
    else if(j==(n-1)) e = lattice[(n-1)*n+n-1]*(lattice[(n-1)*n+n-2]+lattice[(n-1)*n-1]+lattice[n-1]+lattice[n*(n-1)]);
    else e = lattice[j+n*(n-1)]*(lattice[j+n*(n-1)-n]+lattice[j]+lattice[j+n*(n-1)+1]+lattice[j+n*(n-1)-1]);

  }
  else{

    if(j==0) e = lattice[i*n]*(lattice[i*n+1]+lattice[i*n+n]+lattice[i*n-n]+lattice[i*n+n-1]);
    else if(j==(n-1)) e = lattice[i*n+n-1]*(lattice[i*n]+lattice[i*n+n-2]+lattice[i*n+n-1+n]+lattice[i*n-1]);
    else e = lattice[i*n+j]*(lattice[i*n+j+1]+lattice[i*n+j-1]+lattice[(i+1)*n+j]+lattice[(i-1)*n+j]);

  }

return e;

}

int energiaVecinos(int *lattice, int n, int idx){

  int de;
  int i = 0;
  int j = idx;

  //tranformo idx en (i,j)
  while(j>=n){
      j = j-n;
      i = i+1;
  }

  de = vecinos(lattice,n,i,j) + vecinos(lattice,n,i+1,j) + vecinos(lattice,n,i-1,j) + vecinos(lattice,n,i,j+1) + vecinos(lattice,n,i,j-1);

  return de;

}
