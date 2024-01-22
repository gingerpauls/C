#include "complex.h"
#include "stdio.h"

ComplexNumber ComplexNumberAdd(ComplexNumber* num1, ComplexNumber* num2) {
	ComplexNumber result;

	result.real = num1->real + num2->real;
	result.imaginary = num1->imaginary + num2->imaginary;

	return result;
}
ComplexNumber ComplexNumberSubtract(ComplexNumber* num1, ComplexNumber* num2) {
	ComplexNumber result;

	result.real = num1->real - num2->real;
	result.imaginary = num1->imaginary - num2->imaginary;

	return result;
}
ComplexNumber ComplexNumberMultiply(ComplexNumber* num1, ComplexNumber* num2) {
	ComplexNumber result;

	result.real = (num1->real * num2->real) - (num1->imaginary * num2->imaginary);
	result.imaginary = (num1->real * num2->imaginary) + (num2->real * num1->imaginary);

	return result;
}
ComplexNumber ComplexNumberDivide(ComplexNumber* num1, ComplexNumber* num2) {
	ComplexNumber result;
	float realNumerator, realDenominator, imaginaryNumerator, imaginaryDenominator;

	realNumerator = (num1->real * num2->real) + (num1->imaginary * num2->imaginary);
	realDenominator = ((num2->real)*(num2->real)) + ((num2->imaginary)*(num2->imaginary));

	imaginaryNumerator = (num1->imaginary * num2->real) - (num1->real * num2->imaginary);
	imaginaryDenominator = realDenominator;

	result.real = realNumerator / realDenominator;
	result.imaginary = imaginaryNumerator / imaginaryDenominator;

	return result;
}

void PrintComplexNumber(ComplexNumber* result) {
	if (result->imaginary < 0) {
		result->imaginary *= -1;
		printf("%.6g - j %.6g \n", result->real, result->imaginary);
	}
	else {
		printf("%.6g + j %.6g \n", result->real, result->imaginary);
	}
}