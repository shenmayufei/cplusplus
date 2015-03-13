/**
** Clear all but lease significant n bits of x
** Examples: x = 0x78abcdef, n ==8 --> 0xef,  n = 16--> 0xcdef
** Assume 1 <= n <= w
** be attention when n = w, x >> w == x >> 0
** csapp p157 2.68
*/

#include <stdio.h>
#include <stdlib.h>

extern int isValidInteger(const char * str);
extern int str2integer(const char * str);
extern int show_int(int x);


int lower_bits(int x, int n)
{
    int af = (1 << n) - 1;
    int sign = n/sizeof(int)/8;
    sign = -sign;
    int mask =  sign | af;

    return mask & x; 
}

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("Usage: ./0268 0x78abcdef 16\n");
        return -1;
    }

    if(isValidInteger(argv[1]) && isValidInteger(argv[2]))
    {
        int x = str2integer(argv[1]);
        int n = str2integer(argv[2]);
        show_int(lower_bits(x, n));
    }
    else
    {
        printf("the Input is not valid integer\n");
    }
    return 0;
}
