/**
** return 1 when  x contains an even number of 1's; 0 otherwise
** Assume w=32
** requirement: at most 12 arithmetic, bit-wise, and logical operations
** csapp p156 2.65
*/

#include <stdio.h>
#include <stdlib.h>

extern int isValidInteger(const char * str);
extern int str2integer(const char * str);

int even_ones_15(unsigned x)
{
   unsigned ret = (0x0000ffff & x) ^ (x >> 16);
   ret =  (0x000000ff & ret ) ^ ( ret >> 8);
   ret = (0x0000000f & ret ) ^ ( ret >> 4);
   ret = (0x00000003 & ret ) ^ ( ret >> 2);
   ret = (0x00000001 & ret ) ^ ( ret >> 1);

   return !ret;
}

int even_ones(unsigned x)
{
    unsigned ret = x ^ (x >> 16);
    ret = ret ^ ( ret >> 8 );
    ret = ret ^ ( ret >> 4 );
    ret = ret ^ ( ret >> 2 );
    ret = ret ^ ( ret >> 1 );
    ret = 1 & ret;
    return !ret;

}

int main(int argc, char * argv[])
{
    int i = 0;
    if(argc < 2)
    {
        printf("Usage: ./test_02_64 [num]\n for example, ./test_02_64 0xffffffff\n");
        return -1;
    }
    
    const char * param = argv[1];
    if(isValidInteger(param))
    {
        unsigned num = str2integer(param);
        printf("Input string = %s, num = %u, even_ones = %d\n", param,  num, even_ones(num));
    }
    else
    {
        printf("\"%s\" is not a valid integer\n", param);
    }
   
    return 0;
}
