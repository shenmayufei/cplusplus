# Date class

The code is the homework of mooc.study.163.com class "面向对象高级编程（上）"->homework 1, detailed requirements are as follows:
```
为Date类实现如下成员：
1. 构造器，可以初始化年、月、日。
2. 大于、小于、等于（> 、< 、==）操作符重载，进行日期比较。
3. print() 打印出类似 2015-10-1 这样的格式。

然后创建两个全局函数：
1. 第1个函数 CreatePoints生成10个随机的Date，并以数组形式返回；
2. 第2个函数 Sort 对第1个函数CreatePoints生成的结果，将其按照从小到大进行排序。

最后在main函数中调用CreatePoints，并调用print将结果打印出来。然后调用Sort函数对前面结果处理后，并再次调用print将结果打印出来。
```

# Build & Run
```
# compile with g++ in commandline
g++ -I`pwd` date-test.cpp -o date
# run 
./date
# compress code 
zip -r date.zip .
```