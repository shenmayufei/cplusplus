#include <iostream>

class Node {
public:
    Node() { std::cout << "Node()" << std::endl; }
    ~Node() { std::cout << "~Node()" << std::endl; }
};

class Base 
{
public:
    Base() { std::cout << "Base()" << std::endl; }
    virtual ~Base() { std::cout << "~Base()" << std::endl; }
};

class Derived : public Base
{
public:
    Derived()  { std::cout << "Derived()"  << std::endl;  m_pNode = new Node(); }
    virtual ~Derived() { std::cout << "~Derived()" << std::endl;  delete m_pNode; }

private:
    Node* m_pNode;
};

