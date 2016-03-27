#include <stdio.h>
/**
    Figure 3.6 C and assembly code for exchange routine body. The stack set-up and completion portions have been omitted
    Page 209
*/
int exchage(int *xp, int y) 
{
    int x = *xp;
    *xp = y;
    return x;
}

int main() {
    int a = 4;
    int b = exchange(&a, 3);
    printf("a = %d, b = %d\n", a, b);
}
