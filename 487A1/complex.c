#include "complex.h"
#include "stdio.h"
#include "io.h"

void InteractiveMode(void) {
	struct Complex num1, num2, result;

	char operation = NULL;
	char inputbuffer[100];
	if (_isatty(_fileno(stdin))) {
		fprintf(stderr, "Complex calculator\n\n");
		fprintf(stderr, "Type a letter to specify the arithmetic operator (A, S, M, D)\n");
		fprintf(stderr, "followed by two complex numbers expressed as pairs of doubles.\n");
		fprintf(stderr, "Type Q to quit.\n\n");
	}
	while ((operation != 'Q') && (operation != 'q')) {
		if (_isatty(_fileno(stdin))) {
			fprintf(stderr, "Enter exp: ");
		}
		
		fgets(inputbuffer, sizeof(inputbuffer), stdin);
		sscanf(inputbuffer, "%c %f %f %f %f", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

		switch (operation)
		{
		case 'A':
		case 'a':
			result = ComplexAdd(num1, num2);
			PrintResult(result);
			break;
		case 'S':
		case 's':
			result = ComplexSubtract(num1, num2);
			PrintResult(result);
			break;
		case 'M':
		case 'm':
			result = ComplexMultiply(num1, num2);
			PrintResult(result);
			break;
		case 'D':
		case 'd':
			result = ComplexDivide(num1, num2);
			PrintResult(result);
			break;
		case 'Q':
		case 'q':
			//printf("Quitting....\n");
			break;
		default:
			printf("Invalid operation.\n");
			break;
		}
	}
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

void PrintResult(struct Complex result) {
	if (result.imaginary < 0) {
		result.imaginary *= -1;
		printf("%.6g - j %.6g \n", result.real, result.imaginary);
	}
	else {
		printf("%.6g + j %.6g \n", result.real, result.imaginary);
	}
}