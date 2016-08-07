## 作业1 60分
1. 分别给出类型Fruit和Apple的类型大小（即对象size），并通过画出二者对象模型图以及你的测试来解释该size的构成原因。

`tips: 该文档使用markdown格式编写，推荐使用Markdown阅读器查看。`

## 答案

### 编译、运行

```
g++ -o fruit test-header.cpp -lm
./fruit
```

### UML图
UML 图使用 Visual Paradigm 绘制，专门针对 C++ 的设置参考[这里](http://forums.visual-paradigm.com/posts/list/287581.html "virtual")。

### 结果及分析

#### 32 bit 

32位的编译器下， int、long、double、void* 长度均为4字节。因此 Fruit 类大小是 16字节，Apple 类大小是24字节。具体看代码：

``` c++
class Fruit{
    int no;          // 32 bit: 4 byte value, no padding
    double weight;   // 32 bit: 4 byte value, no padding
    char key;        // 32 bit: 1 byte value, 3 byte padding
public:
    void print() {   }
    virtual void process(){   }  // 32 bit: 4 byte, no padding
};
    
class Apple: public Fruit{  // inheritates 12 bytes from Fruit (excluding Fruit's vptr to virtual function table)
    int size;               // 4 bytes value, no padding 
    char type;              // 1 byte value, 3 bytes padding
    void save() {   }
    virtual void process(){   }   // 32 bit: 4 byte, no padding)
};
```

#### 64 bit

目前，不管是桌面还是服务器端，程序已经全面进入 64位的时代。ARM 架构的移动端处理器在向 64位转型。

64位编译器下，int 仍然是 4字节， long、double、void* 长度为 8字节，因此如果一个 class 的成员变量达不到 8字节，编译器会进行padding。

`注意： 32位编译器下，padding的单位是4字节；64位下，padding的单位是 8字节。`

64位编译器下，Fruit 类的大小是 32字节，Apple 类的大小是40字节。具体看代码：

``` c++
class Fruit{
    int no;          // 64bit: 4 byte value, 4 byte padding 
    double weight;   // 64bit: 8 byte, no padding 
    char key;        // 64bit: 1 byte value, 7 bytes padding
public:
    void print() {   }
    virtual void process(){   }  // 64bit: vptr, 8 bytes 
};
    
class Apple: public Fruit{  // inheritates 24 bytes from Fruit (excluding Fruit's vptr)
    int size;               // 4 bytes value, no 
    char type;              // 1 byte value, 3 bytes padding
    void save() {   }
    virtual void process(){   }   // 64bit: vptr 8 bytes
};
```

需要注意的是，编译器会对Apple的成员变量 size 和 type 存放到一起，然后进行padding。 

参考文献：

1. [padding和alignment](http://en.cppreference.com/w/cpp/language/object "alignment")
2. [Fundamental Types (C++)](https://msdn.microsoft.com/en-us/library/cc953fe1.aspx "fundamental types")