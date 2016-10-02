#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Numerical Recipes Routines (from 2nd Ed.)
double *dvector( long nl, long nh );
void free_dvector( double *v, long nl, long nh );
double **dmatrix( long nrl, long nrh, long ncl, long nch );
void free_dmatrix( double **m, long nrl, long nrh, long ncl, long nch );
