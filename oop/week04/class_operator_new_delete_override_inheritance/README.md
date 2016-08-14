
什么时候调用自定义 delete 的重载版本

写继承体系时，也没有调用，

这么来看，operator delete 的重载没有任何意义。

```
g++ -o main spec1_the_operator_new_function1.cpp -std=c++11
./main
```
