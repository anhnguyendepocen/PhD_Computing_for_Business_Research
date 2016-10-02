#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "predict.h"



// Structure
struct dist_st{
  double y;
  double dist;
};

void knn_predict(double **x_train, double *y_train, double **x_test, double *y_test, int k, int numObs, int numParams, int numObsTest){

  double *xi_test, *xj;

  for (i = 0; i < numObsTest; i++){
    // struct dist_st contains 
    //  1. dist: distance between xi_new and xj 
    //  2. y: y value corresponding to xj
    // We sort y values in dist_st_arr according to the increasing order of distance

    struct dist_st* dist_st_arr = (struct dist_st*) malloc(numObs * sizeof(struct dist_st));
    
    // xi_new is ith row of the matrix x_test
    xi_test = dvector(0, numParams - 1);
    for (int l = 0; l < numParams; l++)
    {
      xi_test[l] = x_test[i][l];
    }
    
    for (int j = 0; j < numObs; j++)
    {
      // xj is the jth row of the matrix x
      xj = dvector(0, numParams - 1);
      for (int l = 0; l < numParams; l++) xj[l] = x_train[j][l];

      // calculate the distance between xi_test and xj
      dist_st_arr[j].dist = dist_euclidean(numParams, xi_test, xj);
      dist_st_arr[j].y = y_train[j];
      free_dvector(xj, 0, numParams - 1);
    }
    free_dvector(xi_test, 0, numParams - 1);
    
    // sort the dist_st_arr according to the increasing order of dist
    qsort(dist_st_arr, numObs, sizeof(struct dist_st), struct_cmp_by_dist);
    
    // take average of k nearest neighbors
    y_test[i] = 0.0;
    for (int l = 0; l < k; l++){
      y_test[i] += dist_st_arr[l].y / (double)k;
    }

    // free memory
    free(dist_st_arr);
  }
}

int struct_cmp_by_dist(const void *a, const void *b){
  struct dist_st* ia = (struct dist_st*) a;
  struct dist_st* ib = (struct dist_st*) b;
  //long scaler = 1e10;
  return (int)(100000.f * ia->dist - 100000.f * ib->dist);
  // returns negative if a < b and positive if a > b. 
  // We multiplied result by 100000.0 to preserve decimal precision.
}

double dist_euclidean(int m, double *x1, double *x2){
  // Return Euclidean distance between x1[] and x2[].
  // The indexes of x1 and x2 are i=0,...,m-1.

  double dist;

  if(m==0)  return 0;

  dist = 0.0;
  for(int i = 0 ; i < m ; i++){
    dist += (x1[i] - x2[i]) * (x1[i] - x2[i]);
  }
  
  return sqrt(dist/(double)m);
}

void parse(char *record, char *delim, char arr[][32],int *fldcnt)
{
  // supplementary function called by readCsv

    char *p = strtok(record,delim); //A sequence of calls to this function split str into tokens, 
  //which are sequences of contiguous characters separated by any of the characters that are part of delimiters.
    int fld=0;
 
    while(p){
        strcpy(arr[fld],p);
    fld++;
    p=strtok('\0',delim);
  }
  *fldcnt=fld;
}

double** readCsv(char* fileName, int* m, int* n){
  // Read data from "filename"
  // The data must contain numeric values only.
  // Output:
  //  - data matrix of dimension m by n
  
  char tmp[1024];
  //char tmp[1024]={0x0};
  int fldcnt=0;
  char arr[200][32]={0x0};
  FILE *file;

  int row, col;
  double** data;
  row = 0; col = 0;

  file = fopen(fileName, "r");
  // fopen_s(&file, fileName, "r");
  if(file==NULL)
  {
    printf("Cannot open %s\n", fileName);
    return 0;
  }

  *n = 0; *m = 0;
  while(fgets(tmp,sizeof(tmp),file)!=0) // read a record 
  { 
    parse(tmp,",",arr,&fldcnt);    // whack record into fields 
    *n = fldcnt;
    *m = *m + 1;
  }
    fclose(file);

  data = dmatrix(0, *m - 1, 0, *n - 1);

  file = fopen(fileName, "r");
  //fopen_s(&file, fileName, "r");
  while(fgets(tmp,sizeof(tmp),file)!=0) // read a record 
  { 
    parse(tmp,",",arr,&fldcnt);    // whack record into fields 
    for(int i = 0; i < fldcnt; i++){
      data[row][col] = atof(arr[i]);
      col++;
    }
    row++;  col = 0;
  }
    fclose(file);

  return data;
}

