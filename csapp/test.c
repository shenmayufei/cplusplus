#include <stdio.h>
int main()
{
    int i;
    int a;
    a = 16777216;
    for(i = 0; i < 10; i++)
    {
        printf("%d, %lf\n", a+i, (float)(a+i));
    }
}
