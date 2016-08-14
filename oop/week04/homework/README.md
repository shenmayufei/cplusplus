## 请使用 Markdown 编辑器查看（github、有道云笔记、v2ex、segmentfault等）

## 简介
作业包括下面几个文件：

```
debbydeMBP:homework apple$ tree
.
├── README.md
├── apple.h
├── fruit.h
└── test.cpp

0 directories, 4 files
```

apple.h 和 fruit.h 分别定义了 两个类。 test.cpp 包含了两个测试用例。运行代码请向下看。

注意：这里我重载了 ostream& operator<< ，所以把 print 函数删除了。

## build 
代码在 linux 和 mac 下均编译且运行通过，windows下没有经过测试。

需要注意的是 malloc.h 的位置 在 linux下和 mac下不同：

```
// apple.h
#include <iostream>
#include <sys/malloc.h> // for mac, 可能需要include
#include <malloc.h>     // for linux
```

如果在linux 下编译，需要注释掉 `#include <sys/malloc.h>`；
如果在mac 下面编译，主要注释掉 `#include <malloc.h>`。

### test operator new/delete
测试 operator new 和 operator delete时，需要在main 函数中调用 testOperatorNew() 函数

``` c++
int main(int argc, char *argv[]) {
  // testConstructor();
  // cout << "--------------- 测试真正结束 -----------------" << endl;

  testOperatorNew();
}
```
编译方法和打印结果如下：

``` 
debbydeMBP:homework apple$ g++ -o main test.cpp -lm
debbydeMBP:homework apple$ ./main 
---- test operator new/delete start -----


use customized version of operator new/delete:
Apple::operator new( size_t )
Fruit::Fruit(int, double, char)
Apple::Apple(int, double, char, int, char)
Apple::~Apple()
Fruit::~Fruit()
Apple::opeator delete (void*)


use global default version of operator new/delete:
Fruit::Fruit(int, double, char)
Apple::Apple(int, double, char, int, char)
Apple::~Apple()
Fruit::~Fruit()



under inheritance, use customized version of operator new/delete:
Apple::operator new( size_t )
Fruit::Fruit(int, double, char)
Apple::Apple(int, double, char, int, char)
Apple::~Apple()
Fruit::~Fruit()
Apple::opeator delete (void*)


under inheritance, use global default version of operator new/delete:
Fruit::Fruit(int, double, char)
Apple::Apple(int, double, char, int, char)
Apple::~Apple()
Fruit::~Fruit()


---- test operator new/delete finish ----
```

### test constructors and desctructors
测试 构造函数和析构函数时，需要在main 函数中调用 testConstructor() 函数

``` c++
int main(int argc, char *argv[]) {
  testConstructor();
  cout << "--------------- 测试真正结束 -----------------" << endl;

  // testOperatorNew();
}
```
编译方法和打印结果如下：
```
debbydeMBP:homework apple$ g++ -o main test.cpp -lm
debbydeMBP:homework apple$ ./main 
---- test contructor and desctructor start -----
Fruit::Fruit()
Apple::Apple()
a = {no: 0, weight:0, key:, size:0, type:}

Fruit::Fruit(const Fruit&)
Apple::Apple(const Apple&)
b = {no: 0, weight:0, key:, size:0, type:}

Apple::operator new( size_t )
Fruit::Fruit(int, double, char)
Apple::Apple(int, double, char, int, char)
*c = {no: 5, weight:1, key:c, size:5, type:d}
Apple::~Apple()
Fruit::~Fruit()
Apple::opeator delete (void*)

Apple::operator new( size_t )
Fruit::Fruit()
Apple::Apple()
*f = {no: 0, weight:0, key:}
Apple::~Apple()
Fruit::~Fruit()
Apple::opeator delete (void*)

---- test contructor and desctructor finish ----
Apple::~Apple()
Fruit::~Fruit()
Apple::~Apple()
Fruit::~Fruit()
--------------- 测试真正结束 ----------------- 
```