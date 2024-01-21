#include "complex.h"
#include "stdio.h"

void InteractiveMode(void) {
	struct Complex num1, num2;

	printf("Enter two imaginary numbers (Real + Imag): ");

	if (scanf_s("%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary) != 4) {
		fprintf(stderr, "Enter only 4 numbers.\n");
	}
	else {
		// fix format: real +/- j imag
		printf("you entered: %.3g j%.3g, %.3g j%.3g\n", num1.real, num1.imaginary, num2.real, num2.imaginary);
	}

}
void BatchMode(void) {
	struct Complex num1, num2;

	//FILE* imaginarydata = imaginarydata();
	//fgets(); // read input string
	//sscanf(); // parse input string
	//fprintf(); // print the output

	// fread(); // reads from file
	// fwrite(); // writes to file

	if (scanf_s("%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary) != 4) {
		fprintf(stderr, "Enter only 4 numbers.\n");
	}
	else {
		// fix format: real +/- j imag 
		printf("you entered: %.3g j%.3g, %.3g, j%.3g\n", num1.real, num1.imaginary, num2.real, num2.imaginary);
	}
}