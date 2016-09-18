#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void usage (char *progname);


// Main
int main (int argc, char *argv[])
{
	// Check if HelloNum is called with one or two arguments
	if(argc != 2 && argc != 3)
	{
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}

	if(argc = 2)
	{
		int iInput = strtol(argv[1], NULL, 0);  // argv[1] is the user input
		const int MAX = 125;
		// Print to stdout or stderr the correct ouput depending on the value of the input
		if(iInput >= 0 && iInput <= MAX)
		{
			printf("%d", iInput);
		}
		else
		{
			fprintf(stderr, "%d", iInput);
		}
	}

	if(argc = 3)
	{
		int iInput1 = strtol(argv[1], NULL, 0);  // argv[1] is the first user input
		int iInput2 = strtol(argv[2], NULL, 0);  // argv[2] is the second user input
		const int USERMAX = iInput2;
		// Print to stdout or stderr the correct ouput depending on the value of the input
		if (USERMAX > 125 || USERMAX < 0)
		{
			usage (argv[0]);
			exit (1);			
		}

		if(iInput1 >= 0 && iInput1 <= 125)
		{
			printf("%d", iInput1);
		}
		else
		{
			fprintf(stderr, "%d", iInput1);
		}
	}

	return 0;
}


// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}
