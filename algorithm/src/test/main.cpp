#include <iostream>
#include "BinarySearch.hpp"

int main(int argc, char * argv[])
{
    int arrlen = 30;
    int * array = new int [arrlen]; 
    for(int i = 0;i < arrlen; i++) array[i] = 2 * i + 1;
    int result = zhaosl::BinarySearch<int>(array, arrlen, arrlen);
    std::cout << "find key \"" << (arrlen) << "\" in the array at " << result  << ", array[i]: " << array[result] << std::endl;
    result = zhaosl::BinarySearch<int>(array, arrlen, arrlen+2);
    std::cout << "find key \"" << (arrlen+2) << "\" in the array at " << result  << ", array[i]: " << array[result] << std::endl;
    return 0;
}
