#include "stdio.h"

typedef struct {
	float real;
	float imaginary;
} ComplexNumber;

ComplexNumber ComplexNumberAdd(ComplexNumber*, ComplexNumber*);
ComplexNumber ComplexNumberSubtract(ComplexNumber*, ComplexNumber*);
ComplexNumber ComplexNumberMultiply(ComplexNumber*, ComplexNumber*);
ComplexNumber ComplexNumberDivide(ComplexNumber*, ComplexNumber*);

void PrintComplexNumber(ComplexNumber*);