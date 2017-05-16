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
  i = (int)(((float)rand() / (float)RAND_MAX)*n*n);
  return i;

}

int flip(int *lattice, int n, float T, int idx) {

  int deltae,i=0,j;
  float pi;

  //tranformo idx en (i,j)
  j=idx;
  while(j>=n){
      j = j-n;
      i = i+1;
  }
  //printf("i=%d j=%d\n",i,j);
  deltae = 2*vecinos(lattice,n,i,j);

  if(deltae<0) lattice[idx]=lattice[idx]*(-1);
  else{

    pi = exp(-deltae/T);
    if( ((float)rand() / (float)RAND_MAX) < pi ) lattice[idx]=lattice[idx]*(-1);

  }

  return deltae;
}

int energia(int *lattice, int n){

  int i,j;
  int e = 0;

  for(i=0;i<n;i++) for(j=0;j<n;j++) e = e - vecinos(lattice,n,i,j) ;

  return e;

}

int vecinos(int *lattice, int n, int i, int j){

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
