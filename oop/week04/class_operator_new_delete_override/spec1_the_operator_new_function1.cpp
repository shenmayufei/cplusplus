// https://msdn.microsoft.com/en-us/library/kftdy56f.aspx
// spec1_the_operator_new_function1.cpp
#include <cstddef>
#include <iostream>
#include <malloc.h>
#include <memory.h> 

using namespace std;

class Blanks
{
public:
    Blanks(){ }
    Blanks(int dummy){ throw 1; }

    static void* operator new( size_t stAllocateBlock );
    static void* operator new( size_t stAllocateBlock, char chInit );
    static void* operator new( size_t stAllocateBlock, double dInit );
    static void operator delete( void* pvMem );
    static void operator delete( void* pvMem, char chInit);
    static void operator delete( void* pvMem, double dInit);
};

void* Blanks::operator new( size_t stAllocateBlock ) {
    clog << "Blanks::operator new( size_t )\n";
    void* pvTemp = malloc( stAllocateBlock );
    return pvTemp;
}

void* Blanks::operator new( size_t stAllocateBlock, char chInit )
{
    clog << "Blanks::operator new( size_t, char )\n";
    // throw 20;
    void *pvTemp = malloc( stAllocateBlock );
    if( pvTemp != 0 )
        memset( pvTemp, chInit, stAllocateBlock );
    return pvTemp;
}

void* Blanks::operator new( size_t stAllocateBlock, double dInit ) {
    clog << "Blanks::operator new( size_t, double)\n";
    return malloc(stAllocateBlock);
}


void Blanks::operator delete( void* pvMem ) {
    clog << "Blanks::opeator delete (void*)\n";
    free(pvMem);
}

void Blanks::operator delete( void* pvMem, char chInit ) {
    clog << "Blanks::opeator delete (void*, char)\n";
    free(pvMem);
} 

void Blanks::operator delete( void* pvMem, double dInit ) {
    clog << "Blanks::opeator delete (void*, double)\n";
    free(pvMem);
}
// For discrete objects of type Blanks, the global operator new function
// is hidden. Therefore, the following code allocates an object of type
// Blanks and initializes it to 0xa5
int main()
{
   Blanks *a5 = new('c') Blanks;
   delete a5;
   cout << endl;
   Blanks *a6 = new Blanks;
   delete a6;
   cout << endl;
   Blanks *a7 = new(10.0) Blanks(1);
   delete a7;
   cout << endl;
}

