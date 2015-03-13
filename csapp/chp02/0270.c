/**
** Return 1 when x can be represented as an n-bit, 2's complement number; 0 otherwise
** Assume 1 <= n <= w
** csapp p157 2.70
*/

#include <stdio.h>
#include <stdlib.h>

extern int isValidInteger(const char * str);
extern int str2integer(const char * str);
extern int show_int(int x);


int fits_bits(int x, int n)
{
    int w = sizeof(x)<<3;
    int sign = n/w;
    sign = -sign;
    int mask = (1 << n) - 1; // initial mask
    mask = mask | sign;    // adjusted for n = 32
    return mask==(mask | x);
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
        printf("%s fits into %d bits: %d\n", argv[1], n, fits_bits(x, n)); 
    }
    else
    {
        printf("the Input is not valid integer\n");
    }
    return 0;
}
