/**
** Do rotating right shift.  Assume 0 <= n < w
** Examples when x = 0x12345678 and w = 32:
**  n=4 -> 0x81234567,  n=20 -> 0x45678123
** csapp p157 2.69
*/

#include <stdio.h>
#include <stdlib.h>

extern int isValidInteger(const char * str);
extern int str2integer(const char * str);
extern int show_int(int x);


unsigned rotate_right(unsigned x, int n)
{

    int w = sizeof(x) << 3;
    int left = x << (w-n);
    int sign = 1 - n/w;
    sign = -sign;
    int r_mask = (1 << (w-n)) -1; // initial mask
    r_mask = r_mask | sign;   // adjusted for n =0
    int right = r_mask & (x>>n);

    return left | right; 
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
        show_int(rotate_right(x, n));
    }
    else
    {
        printf("the Input is not valid integer\n");
    }
    return 0;
}
