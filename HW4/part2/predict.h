#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "recipes.h"


// Function declaration
void knn_predict(double **x, double *y, double **x_new, double *y_new, int k, int numObs, int numParams, int numObsNew);
int struct_cmp_by_dist(const void *a, const void *b);
double dist_euclidean(int n, double *x1, double *x2);
double** readCsv(char* fileName, int* m, int* n);
