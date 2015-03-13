/**
** csapp p153 is_big_endian(...)
** @author zhaoshuailong
** @date 2015-01-07 12:57
*/
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char * byte_pointer;

int is_big_endian()
{
    int num = 0x12345678;
    int a, b;
    a = num >> 24; 
    b = ((byte_pointer)(&num))[0];
    printf("a = %d, b = %d\n", a, b);
    return a==b;
    
}

int main()
{
    printf("Is big: %d\n", is_big_endian()) ;
    return 0;
}
