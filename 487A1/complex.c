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

	num1.real = num1.imaginary = 0;
	num2.real = num2.imaginary = 0;

	FILE* imaginarydata = NULL;
	FILE* results = NULL;
	
	char operation = NULL;

	//open imaginarydata.txt
	imaginarydata = fopen("imaginarydata.txt", "r");
	fscanf(imaginarydata, "%c %f %f %f %f ", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

	//char inputbuffer[100] = { 0 };
	//fread(inputbuffer, sizeof(char), sizeof(inputbuffer), imaginarydata);
	//sscanf_s(inputbuffer, "%c %f %f %f %f ", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

	// do the operation
	switch (operation)
	{
	case 'A':
	case 'a':
		printf("adding\n");
		break;
	case 'S':
	case 's':
		printf("subtracting\n");
		break;
	case 'M':
	case 'm':
		printf("multiplying\n");
		break;
	case 'D':
	case 'd':
		printf("dividing\n");
		break;
	default:
		break;
	}

	// open results.txt
	results = fopen("results.txt", "w");
	fprintf(results, "%c %f %f %f %f \n", operation, num1.real, num1.imaginary, num2.real, num2.imaginary);
	//fprintf(results, "%.3g j%.3g %.3g j%.3g\n", 1.34, -52.0, 134,1);



	fclose(imaginarydata);
	fclose(results);

}