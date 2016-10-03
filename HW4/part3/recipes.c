#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "recipes.h"


// data structure routines (dvector and dmatrix) from Numerical Recipes in C (2nd Ed.)

void nrerror( char error_text[] )
{
  // Numerical Recipes standard error handler
  fprintf( stderr,"Numerical Recipes run-time error...\n" );
  fprintf( stderr,"%s\n",error_text );
  fprintf( stderr,"...now exiting to system...\n" );
  exit(1);

} // end of nrerror

double *dvector( long nl, long nh )
{
  // allocate a double vector with subscript range v[nl..nh]

  double *v;

  v=(double *)malloc((size_t) ((nh-nl+2)*sizeof(double)));
  if (!v) nrerror("allocation failure in dvector()");
  return v-nl+1;

} // end of dvector

void free_dvector( double *v, long nl, long nh )
{
  // free a double vector allocated with dvector()

  free((char*) (v+nl-1));

} // end of free_dvector

double **dmatrix( long nrl, long nrh, long ncl, long nch )
{
  // allocate a double matrix with subscript range m[nrl..nrh][ncl..nch]

  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  double **m;

  // allocate pointers to rows
  m=(double **) malloc((size_t)((nrow+1)*sizeof(double*)));
  if (!m) nrerror("allocation failure 1 in dmatrix()");
  m += 1;
  m -= nrl;

  // allocate rows and set pointers to them
  m[nrl]=(double *) malloc((size_t)((nrow*ncol+1)*sizeof(double)));
  if (!m[nrl]) nrerror("allocation failure 2 in dmatrix()");
  m[nrl] += 1;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  // return pointer to array of pointers to rows
  return m;

} // end of dmatrix 

void free_dmatrix( double **m, long nrl, long nrh, long ncl, long nch )
{
  // free a double matrix allocated by dmatrix()

  free((char*) (m[nrl]+ncl-1));
  free((char*) (m+nrl-1));

} // end of free_dmatrix


/**********************************************************************/
void print_mat(char *name, double **ppdEMat, int iMin, int iMax, 
                int jMin, int jMax)
{
  // a simple routine to print the matrix ppdEMat 
  // with row and column headers

  int i, j;

  printf("%s\n ", name);
  for (i = iMin; i <= iMax; i++)     
  { 
      if (i == iMin)
    { 
         for (j = jMin; j <= jMax; j++) printf("%6d ", j);
       printf("\n");
    }

      printf("%2d ", i);
      for (j = jMin; j <= jMax; j++) 
          printf("%6.2lf ", ppdEMat[i][j]);
      printf("\n");
  }
  printf("\n");
 
  return;

}  // end of print_mat

/**********************************************************************/
void print_vec(char *name, double *pdEVec, int iMin, int iMax)
{
  int i;

  printf("%s\n", name);
  for (i = iMin; i <= iMax; i++)
    { printf("%3d  %7.4lf ", i, pdEVec[i]);
      printf("\n");
    }
  printf("\n");
  return;
  
}  // end of print_vec