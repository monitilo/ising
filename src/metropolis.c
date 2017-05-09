#include "metropolis.h"
#include <math.h>
#include "stdlib.h"


int metropolis(int *lattice, int n, float T) {
  int i=0, j=0, r, e;

  idx = pick_site(lattice, n) ;

  e=flip(lattice,n,T,idx)

  return e;
}

int pick_site(int *lattice, int n) { // que hace esto???
  int r;
  r=rand() % ((n*n)-1) ;

    """
    j = r
    while (j>n){
      j = j-n;
      i=i+1;
    }
  """
  return r;
}

int flip(int *lattice, int n, float T, int idx) {
  int e0, e, deltae, p;
  float pi;
  e0 = energia(lattice,n);

  lattice[idx]=lattice[idx]*(-1);

  deltae = energia(lattice,n) - e0 ;

  pi=exp(-deltae/T)

  if pi>=1 p=1
  else p = (((float)rand() / (float)RAND_MAX) < pi)

  if p==0   lattice[idx]=lattice[idx]*(-1);
  else e = energia(lattice,n)

  return e;
}

int energia (int *lattice, int n){
  int i,j,e=0;

  //primero para los casos de los bordes
  e = e + lattice[0*n+0]*(lattice[1]+lattice[n-1]+lattice[n]+lattice[n*(n-1)]);

  e = e + lattice[0*n-1]*(lattice[0]+lattice[n-1-1]+lattice[n-1+n]+lattice[(n*n)-1]);

  e = e + lattice[(n-1)*n+0]*(lattice[(n-1)*n+1]+lattice[((n-1)*n)-n]+lattice[(n*n)-1]+lattice[0]);

  e = e + lattice[(n*n)-1]*(lattice[(n*n)-1]+lattice[(n*n)-n]+lattice[n-1]+lattice[(n-1)*n]);

  // los bordes
  for(j=0;j<n-2;j++) {

    e = e + lattice[j]*(lattice[j+1]+lattice[j-1]+lattice[j+n]+lattice[j+(n*n-1)]);
    e = e + lattice[(n-1)*n+j]*(lattice[(n-1)*n+j+1]+lattice[(n-1)*n+j-1]+lattice[(n-1)*n+j-n]+lattice[0+j]);
    i = j;
    e = e + lattice[i*n]*(lattice[i*n+1]+lattice[i*n+n]+lattice[i*n-n]+lattice[i*n+n-1]);
    e = e + lattice[i*n+n-1]*(lattice[i*n]+lattice[i*n+n-1-1]+lattice[i*n-1-n]+lattice[i*n-1)]);
  }

  //ahora para el bulk
  for(i=1;i<n-1;i++){
    for(j=1;j<n-1;j++){

      e = e + lattice[i*n+j]*(lattice[i*n+j+1]+lattice[i*n+j-1]+lattice[i*(n+1)+j]+lattice[i*(n-1)+j]);

    }
  }
  return e ;
}
