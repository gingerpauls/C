#include "complex.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "io.h"

#define STRING_MAX_SIZE 128

char inputdata[STRING_MAX_SIZE] = "";

int main(int numArguments, char* arguments[]) {
	if (_isatty(_fileno(stdin))) {
		InteractiveMode();
	}
	else {
		BatchMode();
	}

	return 0;
}