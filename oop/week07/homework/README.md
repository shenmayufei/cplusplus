## 描述
假设有个计算类Calculator，它要处理int, long, float, double等数值类型。
用模板实现GetLimit()方法，获得每种类型的数值的上限LIMIT，比如int的上限是100，
long的上限是 1000，float的上限是999.99，double的上限是888.8888888等等。

## build & run

```
# build
g++ -o main main.cpp -lm -std=c++11
# run
./main 
```

### 输出

```
max int:   100                                                                                                               
max long:  1000                                                                                                              
max float: 999.99                                                                                                            
max double:888.889   
```