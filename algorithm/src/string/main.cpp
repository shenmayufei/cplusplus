#include <iostream>
#include "kmp.hpp"

int main(int argc, char * argv[])
{
    std::string pattern("abcdaabcab");
    std::string target("abcddabcababcdaabcababcdaabcabaa");

    int* next = findNext(pattern);
    std::cout << next << std::endl;
    int res = kmp(target, pattern,next);
    std::cout << "pattern:          " << pattern << std::endl;
    std::cout << "target :          " << target  << std::endl;
    std::cout << "result :          " << res     << std::endl;
    return 0;
}
