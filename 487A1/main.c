#include "complex.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#define STRING_MAX_SIZE 128

char inputdata[STRING_MAX_SIZE] = "";

int main(int numArguments, char* arguments[]) {

	bool invalid = false;
	if (numArguments == 1) {
		InteractiveMode();
	}
	else if (numArguments == 2) {
		if (strcmp(arguments[1], "-b") == 0) {
			BatchMode();
		}
		else {
			invalid = true;
		}
	}
	else {
		invalid = true;
	}

	if (invalid) {
		fprintf(stderr, "Unknown or missing arguments.\n\n");
		fprintf(stderr, "-i\t\tInteractive mode (user input/output).\n");
		fprintf(stderr, "-b\t\tBatch mode(inputdata.txt input/output outputdata.txt).\n");
		fprintf(stderr, "Enter only 4 numbers (Real + Imag).\n\n");
	}

	return 0;
}