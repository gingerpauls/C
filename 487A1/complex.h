void InteractiveMode(void);
void BatchMode(void);


struct Complex {
	float real = 0.0;
	float imaginary = 0.0;
};

struct Complex ComplexAdd(struct Complex, struct Complex);
struct Complex ComplexSubtract(struct Complex, struct Complex);
struct Complex ComplexMultiply(struct Complex, struct Complex);
//struct Complex ComplexDivide(struct Complex, struct Complex);