#include "stdio.h"

int add(int x, int y);
int subtract(int x, int y);
int multiply(int x, int y);
int divide(int x, int y);

int do_operation(int x, int y, int (*operation)(int, int));

int main(void) {
    int result = 0;
    result = do_operation(2, 3, add);
    printf("%d\n", result);
    result = do_operation(6, 9, subtract);
    printf("%d\n", result);
    result = do_operation(10, 5, multiply);
    printf("%d\n", result);
    result = do_operation(100, 2, divide);
    printf("%d\n", result);

    return 0;
}

int add(int x, int y) {
    int result;
    return result = x + y;
}
int subtract(int x, int y) {
    int result;
    return result = x - y;
}
int multiply(int x, int y) {
    int result;
    return result = x * y;
}
int divide(int x, int y) {
    int result;
    if (y > 0) {
        return result = x / y;
    }
    else {
        return -1;
    }
}
int do_operation(int x, int y, int (*operation)(int, int)) {
    return operation(x, y);
}