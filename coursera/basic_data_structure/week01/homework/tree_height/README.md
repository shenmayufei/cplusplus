# build & run

```
# build
g++ -o main tree-height.cpp

# run 
./main < tests/1

# test
for file in $(ls tests | grep -v ".a"); do ./main < tests/${file} > tests/${file}.a; done
```