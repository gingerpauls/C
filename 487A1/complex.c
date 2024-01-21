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
	struct Complex num1, num2, result;

	num1.real = num1.imaginary = 0;
	num2.real = num2.imaginary = 0;

	FILE* imaginarydata = NULL;
	FILE* results = NULL;
	
	char operation = NULL;

	//open imaginarydata.txt
	imaginarydata = fopen("imaginarydata.txt", "r");
	results = fopen("results.txt", "w");

	while (!feof(imaginarydata)){
		fscanf(imaginarydata, "%c %f %f %f %f ", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

		//char inputbuffer[100] = { 0 };
		//fread(inputbuffer, sizeof(char), sizeof(inputbuffer), imaginarydata);
		//sscanf_s(inputbuffer, "%c %f %f %f %f ", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

		switch (operation)
		{
		case 'A':
		case 'a':
			result = ComplexAdd(num1, num2);
			
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
		case 'Q':
		case 'q':
			printf("Quitting....");
			break;
		default:
			printf("Quitting....");
			break;
		}

		
		fprintf(results, "%.3g j%.3g \n", result.real, result.imaginary);
		//fprintf(results, "%c %.3g j%.3g %.3g j%.3g \n", operation, num1.real, num1.imaginary, num2.real, num2.imaginary);
		//fprintf(results, "%.3g j%.3g %.3g j%.3g\n", 1.34, -52.0, 134,1);
	}

	fclose(imaginarydata);
	fclose(results);

}

struct Complex ComplexAdd(struct Complex num1, struct Complex num2) {
	struct Complex result;
	result.real = num1.real + num2.real;
	result.imaginary = num2.imaginary + num2.imaginary;
	return result;
}