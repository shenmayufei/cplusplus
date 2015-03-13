/**
** show how data of different types are stored in disk
** @author csapp
** @date 2015-01-08 00:24
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_double(double x)
{
    show_bytes((byte_pointer)&x, sizeof(double));
}

void show_pointer(void* x)
{
    show_bytes((byte_pointer)&x, sizeof(void *));
}

/**
int main()
{
    int a = 12345;
    float  b = (float)a;
    double c = (double)b;
    int * d = &a;

    show_int(a);
    show_float(b);
    show_double(c);
    show_pointer(d);
    
    return 0;
}
*/
