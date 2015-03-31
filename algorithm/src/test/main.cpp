#include <iostream>
#include "BinarySearch.hpp"

class A
{
public:
    A(){ std::cout << "A constructor\n";};
    ~A(){ std::cout << "A destructor\n";};

};

class B : public A
{
public:
    B() {std::cout << "B constructor\n";}
    ~B() {std::cout << "B destructor\n"; }
};

void testInheritance()
{
    B b;
}
int main(int argc, char * argv[])
{
    int arrlen = 30;
    int * array = new int [arrlen]; 
    for(int i = 0;i < arrlen; i++) array[i] = 2 * i + 1;
    int result = zhaosl::BinarySearch<int>(array, arrlen, arrlen);
    std::cout << "find key \"" << (arrlen) << "\" in the array at " << result  << ", array[i]: " << array[result] << std::endl;
    result = zhaosl::BinarySearch<int>(array, arrlen, arrlen+2);
    std::cout << "find key \"" << (arrlen+2) << "\" in the array at " << result  << ", array[i]: " << array[result] << std::endl;

    testInheritance();
    return 0;
}
