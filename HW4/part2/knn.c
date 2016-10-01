// knn.c
// Author: Dongwook Shin, 2014/08/08
// This program illustrates k-nearest neighbors algorithm.
// Input:
//	- knn_train_data.csv
//		- The first column is y_train vector
//		- The rest columns are x_train matrix
//	- knn_test_data.csv
//		- x_test matrix for which we predict y_test values
//	- The files must be located in the same folder as the .exe file.
// Output:
//	- y_test vector that corresponds to x_test matrix input.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "recipes.h"
#include "predict.h"


int main(){
	double **train_data, **test_data;
	double **x_train, *y_train, **x_test, *y_test;
	int i, j, l, m1, n1, m2, n2, k;
	int numObsTrain, numParams, numObsTest;
	char* trainFileName = "knn_train_data.csv";
	char* testFileName = "knn_test_data.csv";

	// set k
	k = 3;

	// Step 1. Import data from a file.
	//	in_sample_data is a matrix of dimension m1 by n1
	//		- the first column of the matrix is y vector
	//		- the rest columns of the matrix are x matrix
	//	out_of_sample_data is a matri of dimension m2 by n2
	//		- the whole matrix is x_new matrix
	train_data = readCsv(trainFileName, &m1, &n1);
	test_data = readCsv(testFileName, &m2, &n2);

	// Step 2. Translate the input data into x, y, and x_new variables
	//	x is a matrix of dimension (numObs) by (numParams)
	//	y is a vector of length (numObs)
	//	x_new is a matrix of dimension (numObsNew) by (numParams)
	numObsTrain = m1;
	numParams = n2;		// must be n2 = n1 - 1
	numObsTest = m2;

	if (n1 - 1 != numParams){
		printf("File read error: Dimensions of matrix x and matrix x_new do not match\n");
		return 1;
	}
	if (numObsTrain <= k){
		printf("File read error: Number of observations must be greater than k\n");
		return 1;
	}

	// translate in-sample data to x matrix and y vector
	x_train = dmatrix(0, numObsTrain - 1, 0, numParams - 1);
	y_train = dvector(0, numObsTrain - 1);
	for (i = 0; i < numObsTrain; i++){
		// first column is y
		y_train[i] = train_data[i][0];
		for (j = 1; j < numParams + 1; j++){
			x_train[i][j-1] = train_data[i][j];	
		}
	}

	// translate out-of-sample data to x_new matrix
	x_test = dmatrix(0, numObsTest - 1, 0, numParams - 1);
	for (i = 0; i < numObsTest; i++){
		for (j = 0; j < numParams; j++){
			x_test[i][j] = test_data[i][j];
		}
	}
	
	// Step 3. Run k-NN algorithm
	y_test = dvector(0, numObsTest - 1);
	knn_predict(x_train, y_train, x_test, y_test, k, numObsTrain, numParams, numObsTest);

	// Step 4. Print prediction result
	printf("\nk-NN train data:\n");
	printf("x_train \t\t | y_train\n");
	for (i = 0; i < numObsTrain; i++){
		printf("(");
		for (l = 0; l < numParams; l++){
			printf("%3.1lf", x_train[i][l]);
			if (l < numParams - 1)	printf(", ");
		}
		printf(")\t\t | ");
		printf("%3.1lf\n", y_train[i]);
	}

	printf("\nk-NN prediction result for test data with k = %d:\n", k);
	printf("x_test \t\t\t | y_test\n");
	for (i = 0; i < numObsTest; i++){
		printf("(");
		for (l = 0; l < numParams; l++){
			printf("%3.1lf", x_test[i][l]);
			if (l < numParams - 1)	printf(", ");
		}
		printf(")\t\t | ");
		printf("%3.2lf\n", y_test[i]);
	}

	// free memory
	free_dmatrix(x_train, 0, numObsTrain - 1, 0, numParams - 1);
	free_dvector(y_train, 0, numObsTrain - 1);
	free_dmatrix(x_test, 0, numObsTest - 1, 0, numParams - 1);
	free_dvector(y_test, 0, numObsTest - 1);

	return 0;
}
