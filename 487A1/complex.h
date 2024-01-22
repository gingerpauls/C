#include "stdio.h"

void InteractiveMode(void);
void BatchMode(void);

struct Complex {
	float real;
	float imaginary;
};

struct Complex ComplexAdd(struct Complex, struct Complex);
struct Complex ComplexSubtract(struct Complex, struct Complex);
struct Complex ComplexMultiply(struct Complex, struct Complex);
struct Complex ComplexDivide(struct Complex, struct Complex);

void PrintResult(struct Complex);