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

	FILE* imaginarydata = NULL;
	FILE* results = NULL;
	
	char operation = NULL;

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
			result = ComplexSubtract(num1, num2);
			printf("subtracting\n");
			break;
		case 'M':
		case 'm':
			result = ComplexMultiply(num1, num2);
			printf("multiplying\n");
			break;
		case 'D':
		case 'd':
			result = ComplexDivide(num1, num2);
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

		if (result.imaginary < 0) {
			result.imaginary *= -1;
			fprintf(results, "%.6g - j%.6g \n", result.real, result.imaginary);
		}
		else {
			fprintf(results, "%.6g + j%.6g \n", result.real, result.imaginary);
		}


		//fprintf(results, "%.3g j%.3g \n", result.real, result.imaginary);
		//fprintf(results, "%c %.3g j%.3g %.3g j%.3g \n", operation, num1.real, num1.imaginary, num2.real, num2.imaginary);
		//fprintf(results, "%.3g j%.3g %.3g j%.3g\n", 1.34, -52.0, 134,1);
	}

	fclose(imaginarydata);
	fclose(results);

}

struct Complex ComplexAdd(struct Complex num1, struct Complex num2) {
	num1.real += num2.real;
	num1.imaginary += num2.imaginary;
	return num1;
}

struct Complex ComplexSubtract(struct Complex num1, struct Complex num2) {
	num1.real -= num2.real;
	num1.imaginary -= num2.imaginary;
	return num1;
}
struct Complex ComplexMultiply(struct Complex num1, struct Complex num2) {
	struct Complex result;

	result.real = (num1.real * num2.real) - (num1.imaginary * num2.imaginary);
	result.imaginary = (num1.real * num2.imaginary) + (num2.real * num1.imaginary);

	return result;
}
struct Complex ComplexDivide(struct Complex num1, struct Complex num2) {
	struct Complex result;
	float realNumerator, realDenominator, imaginaryNumerator, imaginaryDenominator;

	realNumerator = (num1.real * num2.real) + (num1.imaginary * num2.imaginary);
	realDenominator = ((num2.real)*(num2.real)) + ((num2.imaginary)*(num2.imaginary));

	imaginaryNumerator = (num1.imaginary * num2.real) - (num1.real * num2.imaginary);
	imaginaryDenominator = realDenominator;

	result.real = realNumerator / realDenominator;
	result.imaginary = imaginaryNumerator / imaginaryDenominator;

	return result;
}