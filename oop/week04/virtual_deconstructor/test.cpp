#include "header.h"
#include <iostream>

int main() {
    // 注意：Base的析构函数设置为 virtual
    Base *b = new Derived();
    // 使用 b
    delete b; // 结果是：调用了 Base的构造函数

    std::cout << "execute complete" << std::endl;
}
