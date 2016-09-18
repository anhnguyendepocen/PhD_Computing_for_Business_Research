#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void usage (char *progname);


// Main
int main (int argc, char *argv[])
{
	// Check if HelloNum is called with one argument
	if(argc != 2)
	{
		printf("Need an argument.\n");
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}

	int iInput = strtol(argv[1], NULL, 0);  // argv[1] is the user input

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
