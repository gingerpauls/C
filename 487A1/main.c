#include "complex.h"
#include "stdio.h"
#include "io.h"

int isStreamTerminal(void);

int main(int numArguments, char* arguments[]) {

	struct Complex num1, num2, result;

	char operation = NULL;
	char inputbuffer[100];

	if (isStreamTerminal()) {
		fprintf(stderr, "Complex calculator\n\n");
		fprintf(stderr, "Type a letter to specify the arithmetic operator (A, S, M, D)\n");
		fprintf(stderr, "followed by two complex numbers expressed as pairs of doubles.\n");
		fprintf(stderr, "Type Q to quit.\n\n");
	}

	while ((operation != 'Q') && (operation != 'q')) {
		if (isStreamTerminal()) {
			fprintf(stderr, "Enter exp: ");
		}

		fgets(inputbuffer, sizeof(inputbuffer), stdin);
		sscanf(inputbuffer, "%c %f %f %f %f", &operation, &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);

		switch (operation)
		{
		case 'A':
		case 'a':
			result = ComplexAdd(num1, num2);
			PrintComplexNumber(result);
			break;
		case 'S':
		case 's':
			result = ComplexSubtract(num1, num2);
			PrintComplexNumber(result);
			break;
		case 'M':
		case 'm':
			result = ComplexMultiply(num1, num2);
			PrintComplexNumber(result);
			break;
		case 'D':
		case 'd':
			result = ComplexDivide(num1, num2);
			PrintComplexNumber(result);
			break;
		case 'Q':
		case 'q':
			break;
		default:
			printf("Invalid operation.\n");
			break;
		}
	}

	return 0;
}

int isStreamTerminal(void) {
	if (_isatty(_fileno(stdin))) {
		return 1;
	}
	else {
		return 0;
	}
}