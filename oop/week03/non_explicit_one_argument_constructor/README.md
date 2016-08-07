# non explicit one argument  非显式单变量 的默认类型转换

编译器认为必要时，使用 constructor 对 变量进行隐式类型转换

如果不想要隐式转换，则使用 explicit 修饰 constructor

## conversion function 的特征

## 扩展
explicit 修饰的构造函数，与隐式转换 （通过 non-explicit-one-argument constructor）

# build
``` 
g++ -pipe -O2 test-fraction.cpp -lm -o main 
```