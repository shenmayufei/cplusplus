## 推荐使用 Markdown 编辑器阅读

### 作业文件

```
debbydeMBP:homework apple$ tree
.
├── README.md
├── main.cpp
└── programmer.h

0 directories, 3 files
```

# build & run
请使用支持 C++11 的编译器进行编译，否则会报错
``` c++
# build
g++ -o main test.cpp -lm -std=c++11
# run 
./main
# compress code 
zip -r zhaoshuailong09.zip .
```

期望输出：
```
debbydeMBP:homework apple$ g++ -o main main.cpp -lm -std=c++11
debbydeMBP:homework apple$ ./main 
------------print set order by id ---------------
[6]:Andrei Alexandrescu
[5]:Stanley P.Lippman
[4]:P.J.Plaught
[3]:Bill Gates
[2]:Martin Fowler
[1]:Scott Meyers

----------trying to find out {3, L"Bill Gates"}--------
found bill 

------------print set order by name---------------
[6]:Andrei Alexandrescu
[3]:Bill Gates
[2]:Martin Fowler
[4]:P.J.Plaught
[1]:Scott Meyers
[5]:Stanley P.Lippman
```