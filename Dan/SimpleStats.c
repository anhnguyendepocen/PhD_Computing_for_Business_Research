#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void usage (char *progname);


// Main
int main (int argc, char *argv[])
{
	// Check if HelloNum is called with at least one positive integer argument
	if(argc < 2)
	{
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}

	int iMax = strtol(argv[1], NULL, 0);
	int iMin = strtol(argv[1], NULL, 0);
	int iSum = 0;
	int iValid = 0;

	for (int i = 1; i < argc; i++)
	{
		int iCheck = strtol(argv[i], NULL, 0);
		// If the number is valid, keep track of sum, max, and min
		if (iCheck >= 0)
		{	
			iValid++;
			iSum += iCheck;
			if (iCheck < iMin)
			{
				iMin = iCheck;
			}
			if (iCheck > iMax)
			{
				iMax = iCheck;
			}
		}
		// If the number is invalid, print to stderr
		else
		{
			fprintf(stderr, "ERROR: %d invalid\n", iCheck);
			fflush(stderr);

		}
	}

	double dMean = (double)iSum/iValid;

	printf("%d, %d, %d, %1.2f",iValid, iMax, iMin, dMean);
	fflush(stdout);

	return 0;
}


// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer <integer, integer,...>", progname);
}
