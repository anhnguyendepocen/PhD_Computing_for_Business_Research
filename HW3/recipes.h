#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void     print_mat(char *name, double **ppdEMat, int iMin, int iMax, 
                       int jMin, int jMax);
void     print_vec(char *name, double *pdEVec, int iMin, int iMax);
void     mat_vec_mult( double *pdCVec, double **ppdAMat, double *pdBVec, 
                       int iRow, int iCol);
void     nrerror( char error_text[] );
double   *dvector( long nl, long nh );
void     free_dvector( double *v, long nl, long nh );
double   **dmatrix( long nrl, long nrh, long ncl, long nch );
void     free_dmatrix( double **m, long nrl, long nrh, long ncl, long nch );
