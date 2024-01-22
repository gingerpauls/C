#include "complex.h"
#include "stdio.h"

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

void PrintComplexNumber(struct Complex result) {
	if (result.imaginary < 0) {
		result.imaginary *= -1;
		printf("%.6g - j %.6g \n", result.real, result.imaginary);
	}
	else {
		printf("%.6g + j %.6g \n", result.real, result.imaginary);
	}
}