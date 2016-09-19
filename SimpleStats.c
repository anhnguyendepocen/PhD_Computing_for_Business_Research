#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void usage (char *progname);
int max (int *piInput);
int min (int *piInput);
double mean (int *piInput);


// Main
int main (int argc, char *argv[])
{
	// Check if HelloNum is called with at least one positive integer argument
	if(argc < 2)
	{
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}

	// Create a list to store user input and a pointer to keep track of that list
	int iInputList[argc-1];
	int *piInputList;
	piInputList = &iInputList[0];

	for (int i = 1; i < argc; i++)
	{
		int iCheck = strtol(argv[i], NULL, 0);
		if (iCheck >= 0)
		{
			iInputList[i-1] = iCheck;
		}
		else
		{
			fprintf(stderr, "ERROR: %d invalid", iCheck);
		}
	}

	// Calculate the four numbers that will be printed to screen
	int iN = sizeof(piInputList) / sizeof(piInputList[0]);  // Calculate the size of the array
	int iMax = max(piInputList);
	int iMin = min(piInputList);
	double dMean = mean(piInputList);

	printf("%d, %d, %d, %1.2f",iN, iMax, iMin, dMean);

	return 0;
}


// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}

int max (int *piInput)
{
	int iMax = piInput[0];
	int n = sizeof(piInput) / sizeof(piInput[0]);  // Calculate the size of the array
	for (int j = 0; j < n; j++)
	{
		if(piInput[j] > iMax)
		{
			iMax = piInput[j];
		}
	}
	return iMax;
}

int min (int *piInput)
{
	int iMin = piInput[0];
	int n = sizeof(piInput) / sizeof(piInput[0]);  // Calculate the size of the array
	for (int j = 0; j < n; j++)
	{
		if(piInput[j] < iMin)
		{
			iMin = piInput[j];
		}
	}
	return iMin;
}

double mean (int *piInput)
{
	int iSum = 0;
	int n = sizeof(piInput) / sizeof(piInput[0]);  // Calculate the size of the array
	for (int j = 0; j < n; j++)
	{
		iSum += piInput[j];
	}
	double dAvg = (double)iSum/n;
	return dAvg;
}