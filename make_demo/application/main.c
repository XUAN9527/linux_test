#include <stdio.h>
#include <stdarg.h>
#include "common.h"
#include "submake.h"

void va_test(int count, ...) {
    va_list args;
    va_start(args, count);
	printf("va test count = [%d]\nva_param: ", count);
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        printf("%d ", value);			//deal with code
    }
    printf("\n\n");
    va_end(args);
}


int main(int argc, char *argv[])
{
    printf("==Va_test==\n");
    va_test(5, 4, 1, 3, 9, 13);

    List_Node_test();
    radixSort_test();

    subtest_function();

    return 0;
}
