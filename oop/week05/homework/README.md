## 推荐使用 Markdown 编辑器阅读

### 作业文件

```
debbydeMBP:homework apple$ tree
.
├── README.md
├── find_if_not_equal_to.h
├── person.h
└── test.cpp

0 directories, 4 files
```

find_if_not_equal_to.h 是 作业相关的代码
test.cpp 是 main 函数所在的地方
person.h 是 为了方便测试，增加的自定义 class

### 简单介绍
作业要求实现的是 find_if_not_equal_to 函数。这里 我借助于 std::find_if、std::bind、std::not_equal_to 和 std::placeholders:_1 实现，
该函数不仅支持 int、double 等基本类型，也支持自定义类型 (person.h 为例)。

在test.cpp 中，有 testInt 和 testCustomizedType 两个测试用例，分别用于测试 基本类型和自定义类型的结果。

### 编译、运行
std::bind 和 std::placeholders 均是 C++11 新增的，如果你的编译器比较早，建议打开 -std=c++11 进行编译。
具体命令如下：

```
# build
g++ -o main test.cpp -lm -std=c++11
# run 
./main
# compress code 
zip -r zhaoshuailong09.zip .
```

参考文档：

1. [std::bind](http://www.cplusplus.com/reference/functional/bind/ "bind")
2. [std::not_equal_to](http://www.cplusplus.com/reference/functional/not_equal_to/ "not_equal_to")