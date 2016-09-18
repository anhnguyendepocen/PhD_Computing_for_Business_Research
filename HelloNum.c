#include <stdio.h>
#include <stdlib.h>

// Function declarations
void usage (char *progname);


// Main
int main (int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Need an argument.\n");
		usage (argv[0]); // argv[0] is always the program name
		exit (1);
	}


}




// Function Definitions

// usage: takes a program name as an argument and prints a usage error message to stderr
void usage (char *progname)
{
	fprintf(stderr, "ERROR: USAGE: %s integer", progname);
}
