/**
** return 1 when any even bit of x equals 1; 0 otherwise
** csapp p156 2.64
*/

#include <stdio.h>
#include <stdlib.h>

int any_even_one(unsigned x)
{
    unsigned length = sizeof(unsigned) << 3;
    int mask = 2;
    int ret = 1;
    while(0 != length)
    {
        ret = ret && (mask & x);
        x = x >> 2;
        length -= 2;
    }
    return ret;
}

int isValidInteger(const char * str)
{
    if(NULL == str || 0 == str[0])
        return 0;
    if( '0' == str[0])
    {
        if(0 == str[1])
            return 1;
        else if('x' == str[1] || 'X' == str[1])
        {
            int i = 2;
            while(0 != str[i])
            {
                if( str[i] < '0' || (str[i] > '9' && str[i] < 'A') || (str[i] >'F' && str[i] < 'a') || str[i] > 'f' )
                    return 0;
                i++;
            }
        }
        else
        {
            int i = 1;
            while( 0 != str[i])
            {
                if( str[i] < '0' || str[i] > '7')
                    return 0;
                i++;
            }
        }

    }
    else
    {
        int i = 0; 
        while( 0 != str[i])
        {
            if( str[i] < '0' || str[i] > '9')
                return 0;

            i++;
        }

    }

    return 1;
}

unsigned str2integer(const char * str)
{
    unsigned ret = 0;
    if('0' == str[0])
    {
        if( 0 == str[1])
          return 0;
        else if( 'x' == str[1])
        {   //hex 
            int i = 2; 
            while( 0 != str[i])
            {
                if(str[i] >= '0' && str[i] <= '9')
                    ret = 16 * ret + str[i] - '0';
                else if( str[i] >= 'a' && str[i] <= 'f')
                    ret = 16 * ret + str[i] - 'a' + 10;
                else if( str[i] >= 'A' && str[i] <= 'F')
                    ret = 16 * ret + str[i] - 'A' + 10;
                i++;
            }

        }
        else
        {  // oct
            int i = 1;
            while( 0 != str[i] )
            {
                ret = 8 * ret + str[i] - '0';
                i++;
            }
        }
    }
    else
    {
        int i = 0;
        while( 0 != str[i] )
        {
            ret = 10 * ret + str[i] - '0';
            i++;
        }
    }

    return ret;
    
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
        printf("Input string = %s, num = %u, any_even_one = %d\n", param,  num, any_even_one(num));
    }
    else
    {
        printf("\"%s\" is not a valid integer\n", param);
    }
   
    return 0;
}
