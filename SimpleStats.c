#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void usage (char *progname);
int max (int *piInput);
int min (int *piInput);
int mean (int *piInput);


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
		iInputList[i-1] = strtol(argv[i], NULL, 0);
	}

	// Print to stdout or stderr the correct ouput depending on the value of the input
	if(iInput >= 0)
	{
		printf("%d, pos", iInput);
	}
	else
	{
		fprintf(stderr, "%d, neg", iInput);
	}

	return 0;
}


// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}


