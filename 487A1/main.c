#include "complex.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#define STRING_MAX_SIZE 128

char inputdata[STRING_MAX_SIZE] = "";

int main(int numArguments, char* arguments[]) {

	bool invalid = false;

	if (numArguments == 2) {
		if (strcmp(arguments[1], "-i") == 0) {
			// interactive mode function
		}
		if (strcmp(arguments[1], "-b") == 0) {
			// batch mode function
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










	struct Complex num1, num2;

	printf("Enter two imaginary numbers (Real + Imag): ");

	if (scanf_s("%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary) != 4) {
		fprintf(stderr, "Enter only 4 numbers.\n");
	}
	else {
		printf("you entered: %.3g, %.3g, %.3g, %.3g\n", num1.real, num1.imaginary, num2.real, num2.imaginary);
	}

	//sscanf(inputdata, "%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);
	//printf("You entered: \n%f, %f, %f, %f", num1.real, num1.imaginary, num2.real, num2.imaginary);

	//sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",&i, &x, str1, &j, &y, str2, warr)

	//FILE* imaginarydata = imaginarydata();
	//fgets(); // read input string
	//sscanf(); // parse input string
	//fprintf(); // print the output
	// 
	// fread(); // reads from file
	// fwrite(); // writes to file

	return 0;
}