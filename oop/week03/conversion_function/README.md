# conversion function  转换函数

编译器认为必要时，转换为 某种特定的类型

## conversion function 的特征
1. 转换函数 的声明中不需要写return type
2. 函数名为 （operator xxx）
3. 要使用 const 修饰，因为  这类函数不会修改 this的值

## 扩展
explicit 修饰的构造函数，与隐式转换 （通过 non-explicit-one-argument constructor）

# build
``` 
g++ -pipe -O2 test-fraction.cpp -lm -o main 
```