#include "lattice.h"
int fill_lattice(int *lattice, int n, float p) {
  int i;

  for (i=0;i<n*n;i++){

    if (((float)rand() / (float)RAND_MAX) < p) lattice[i] = 1 ;
    else lattice[i] = -1 ;
  }

  return 0;
}

int print_lattice(int *lattice, int n) {
  int i;
	int j;
	for(i=0 ;i<n;i=i+1){

		for(j=0;j<n;j=j+1) printf("%d ", lattice[i*n+j]);

		printf("\n");                //bajo a la siguiente fila
	}
  return 0;
}
