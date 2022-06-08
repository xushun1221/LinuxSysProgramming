#include "head.h"
int main() {
    int a = 10;
    int b = 5;
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", sub(a, b));
    printf("a / b = %d\n", div1(a, b));
    return 0;
}