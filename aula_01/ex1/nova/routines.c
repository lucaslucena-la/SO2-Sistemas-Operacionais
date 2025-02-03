#include <stdio.h>


int sub(int a, int b);
int inc(int a);

int main() {
    int result = sub(20, 5);
    int increment = inc(10);
    printf("icremento%d", increment);
    printf("resultado da sub:%d", result);
    return 0;
}