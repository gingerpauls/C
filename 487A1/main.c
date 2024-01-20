#include "stdio.h"

#define STRING_MAX_SIZE 128

char inputdata[STRING_MAX_SIZE] = "";

struct Complex {
	float real, imaginary;
};

int main(void) {
	struct Complex num1, num2;

	printf("Enter two imaginary numbers: ");

	if (scanf_s("%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary) != 4) {
		fprintf(stderr, "Enter only 4 numbers.\n");
	}
	else {
		printf("you entered: %.3g, %.3g, %.3g, %.3g\n", num1.real, num1.imaginary, num2.real, num2.imaginary);
	}

	//sscanf(inputdata, "%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);
	//printf("You entered: \n%f, %f, %f, %f", num1.real, num1.imaginary, num2.real, num2.imaginary);

	//sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",&i, &x, str1, &j, &y, str2, warr)

	//FILE* imaginarydata = imaginarydata();
	//fgets(); // read input string
	//sscanf(); // parse input string
	//fprintf(); // print the output
	// 
	// fread(); // reads from file
	// fwrite(); // writes to file

	return 0;
}