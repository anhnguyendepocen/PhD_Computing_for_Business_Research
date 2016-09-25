#include <stdio.h>
#include <stdlib.h>
#include "recipes.h"

// Function Prototypes
void usage (char *progname);
double sumcubes (double *pdv, long nl, long nh);


// Main
int main (int argc, char *argv[])
{
	char *FILENAME;
	int iNumLines = 0;
	int iPosLines = 0;
	int iNegLines = 0;
	double *pdPosVec, *pdNegVec;

	// Check if HelloNum is called with an argument
	if(argc < 1 || argc > 2)
	{
		usage (argv[0]);
		exit (1);
	}
	else if(argc == 1)
	{
		FILENAME = argv[1];
		iNumLines = 10;
	}
	else if(argc == 2)
	{
		FILENAME = argv[1];
		iNumLines = strtol(argv[2], NULL, 0);		
	}
	
	// Open two files, one for input and the other for output
	// #define FILE_NAME FILENAME;
	#define OUTFILE "SumCubesOutput.txt"

  	FILE *file_in, *file_out; 

	file_in = fopen(FILENAME, "r");
	if (file_in == NULL)
	{
		fprintf(stderr, "Error Reading File\n");
		exit (1);
	}

	file_out = fopen(OUTFILE, "w");
	if (file_out == NULL){
		fprintf(stderr, "Error Reading File\n");
		exit (1);
	}

	// Step through each line of the file and count the number of lines with a positive number or with a negative number 
	char *line = NULL;
	int iLineIterator = iNumLines;
	while(fgets(line, 50, file_in) != NULL && iLineIterator > 0)
   	{
   		double dNumber;
		sscanf (line, "%lf", &dNumber);
		if(dNumber > 0)
		{
			iPosLines++;
		}
		if(dNumber < 0)
		{
			iNegLines++;
		}
		iLineIterator--;
	}	

	// Finish creating pdPosVec and pdNegVec
	pdPosVec = dvector(1, iPosLines);
	pdNegVec = dvector(1, iNegLines);

	// Create two iterators for filling in the two vectors
	int i=1;
	int j=1;

	// Fill in pdPosVec and pdNegVec
	int iLineIterator2 = iNumLines;
	while(fgets(line, 50, file_in) != NULL && iLineIterator2 > 0)
	{
		double dNumber;
		sscanf (line, "%lf", &dNumber);
		if(dNumber > 0)
		{
			pdPosVec[i] = dNumber;
			i++;
		}
		if(dNumber < 0)
		{
			pdNegVec[j] = dNumber;
			j++;
		}
		iLineIterator2--;
	}

	// Print out pdPosVec and pdNegVec
	print_vec("pdPosVec", pdPosVec, 1, iPosLines);
	print_vec("pdNegVec", pdNegVec, 1, iNegLines);	

	// Call the sumcubes function and print the results to both the screen and the output file
	double dSumCubesPos = sumcubes(pdPosVec, 1, iPosLines);
	double dSumCubesNeg = sumcubes(pdNegVec, 1, iNegLines);
	printf("The sum of cubes for pdPosVec is %lf, while the sum of cubes for pdPosNeg is %lf", dSumCubesPos, dSumCubesNeg);
	fprintf(file_out, "The sum of cubes for pdPosVec is %lf, while the sum of cubes for pdPosNeg is %lf", dSumCubesPos, dSumCubesNeg);

	// Free the vectors
	free_dvector(pdPosVec, 1, iPosLines);
	free_dvector(pdNegVec, 1, iNegLines);
	fclose(file_in);
	fclose(file_out);

	return(0);
}



// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}

// sumcubes: takes a vector of doubles and the range of values as arguments, and returns the sum of the cubes of the elements of this vector
double sumcubes (double *pdv, long nl, long nh)
{
	double sum = 0.0;
	for (int i = nl; i <= nh; i++)
	{
		sum += pdv[i]*pdv[i]*pdv[i];
	}
	return sum;
}


