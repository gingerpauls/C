#include "stdio.h"
#define STRING_MAX_SIZE 128
int main(void) {
	//char* outdata = "Hello World!\n";
	//char indata[10] = 0;
	//float num1real, num1imaginary, num2real, num2imaginary;

	struct Complex {
		float real, imaginary;
	};

	struct Complex num1, num2;

	char inputdata[STRING_MAX_SIZE];
	const char[2] = " ";
	char* token;

	printf("Enter two imaginary numbers: ");


	//fgets(inputdata, sizeof(inputdata), stdin);


	// PARSE
	// %d: an integer 
	// %f: a floating-point value
	// %9s: a string of at most 9 non-whitespace characters
	// %2d: two-digit integer (digits 5 and 6)
	// %f: a floating-point value (digits 7, 8, 9)
	// %*d an integer which isn't stored anywhere
	// ' ': all consecutive whitespace
	// %3[0-9]: a string of at most 3 digits (digits 5 and 6)
	// %2lc: two wide characters, using multibyte to wide conversion

	sscanf(inputdata, "%f %f %f %f", &num1.real, &num1.imaginary, &num2.real, &num2.imaginary);
		//printf("You entered: \n%f, %f, %f, %f", num1.real, num1.imaginary, num2.real, num2.imaginary);

	//sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",&i, &x, str1, &j, &y, str2, warr)

	//printf("\n%s\n", inputdata);

	//printf(outdata);

	//rintf("Input a character: ");
	//scanf(indata);
	//FILE* imaginarydata = imaginarydata();
	//fgets(); // read input string
	//sscanf(); // parse input string
	//fprintf(); // print the output


	// fread(); // reads from file
	// fwrite(); // writes to file

	//outdata = indata;
	//printf(outdata);
	return 0;
}