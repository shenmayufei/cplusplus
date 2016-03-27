/**
    3.2.2 Code example
    Page 196

    Compile options 1: gcc -O1 -S code.c
    Output: code.s (on mac)
    
    Compile options 2: gcc -O1 -c code.c
    Output: code.o
*/
int accum = 0;

int sum(int x, int y)
{
    int t= x + y;
    accum += t;
    return t;
}
