#include <iostream>
#include "HashMap.hpp"

int main(int argc, char* argv[])
{

    std::cout << "HashMap test start\n";
    zhaosl::HashMap<int, int> mymap;
    std::cout << "map.size: " << mymap.size() << std::endl;
    std::cout << "HashMap test end\n\n";
    std::cout << "Exit Main function\n";
}
