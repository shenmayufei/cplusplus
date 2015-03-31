#include <iostream>

#include "BinaryTree.hpp"

int main(int argc, char * argv[])
{

    zhaosl::BinaryTree<int> tr;
    zhaosl::BinaryTree<int> tr2;
    tr.createTree(4, tr2, tr2);
    tr.createTree(1, tr, tr2);
    tr.createTree(2, tr2, tr);
    std::vector<int> vec;
    tr.inOrder(tr.root(), vec);
    for(std::vector<int>::const_iterator cIter = vec.begin(); cIter != vec.end(); cIter ++) std::cout << *cIter << ", ";
    std::cout << std::endl;

    return 0;
}
