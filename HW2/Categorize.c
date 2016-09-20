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
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}

	int iInput = strtol(argv[1], NULL, 0);  // argv[1] is the user input

	// Print to stdout the correct ouput depending on the value of the input
	if(iInput == 0)
	{
		printf("baby");
	}
	else if(iInput > 0 && iInput <= 3)
	{
		printf("toddler");
	}
	else if(iInput > 3 && iInput <= 12)
	{
		printf("child");
	}
	else if(iInput > 12 && iInput <= 19)
	{
		printf("teenagers");
	}
	else if(iInput > 19 && iInput <= 22)
	{
		printf("youngadult");
	}
	else if(iInput > 22 && iInput <= 65)
	{
		printf("adult");
	}
	else if(iInput > 65 && iInput <= 125)
	{
		printf("senior");
	}
	else
	{
		usage (argv[0]); // argv[0] is always the program name
		exit (1);		
	}

	return 0;
}


// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}
