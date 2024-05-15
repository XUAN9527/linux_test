#include <stdio.h>
#include <stdarg.h>
#include "../include/calc.h"

void demo(int count, ...) {
    va_list args;
    va_start(args, count);
	printf("\nva test count = [%d]\nva_param:\n", count);
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        printf("[%d]", value);			//deal with code
    }
    printf("\n");
    va_end(args);
}

int main() {
    int a = 20;
    int b = 12;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));

    demo(4, 10, 20, 30, 40);

    return 0;
}