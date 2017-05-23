#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float J,float B, float *expo, float *e, int *m);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, int idx, float J, float B ,float *expo, float *e, int *m);

float energia(int *lattice, int n, float J, float B);
int vecinos(int *lattice, int n, int idx);
int magnetizacion(int*lattice, int n) ;

#endif
