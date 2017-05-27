/*****
Your task is to calculate ab mod 1337 where a is a positive integer and 
b is an extremely large positive integer given in the form of an array.

Example1:
a = 2
b = [3]

Result: 8


Example2:
a = 2
b = [1,0]

Result: 1024

Ref: https://leetcode.com/problems/super-pow/#/description
*/

#include <iostream>
#include <vector>

using std::vector;


const int mod = 1337;

int superPowHelper(int a, int b) {
    a = a % mod;

    // base conditions
    if (b == 0) {
        return 1;
    }
    if (b == 1) {
        return a;
    }
    int ret = superPowHelper(a, b/2) % mod;
    ret =  (ret * ret) % mod;
    if (b % 2 == 1) {
        ret = (ret * a) % mod;
    }
    return ret;
}

int superPow(int a, vector<int>& b) {
    vector<int> exps(b.size(), a); // a^(10^(b.size-1) ) to a^0
    
    for(int i = exps.size()-2 ; i >= 0; i--) {
        exps[i] = superPowHelper(exps[i+1], 10);
    }

    int ret = 1;
    for(int i = 0; i < exps.size(); i++) {
        ret *= superPowHelper(exps[i], b[i]);
        ret = ret % mod;
    }
    return ret;
}

int main() {
    int a = 2; 
    std::vector<int> *testcases = new std::vector<int>[3];
    testcases[0] = std::vector<int> {3};
    testcases[1] = std::vector<int> {1,0};
    testcases[2] = std::vector<int> {1,0,1};
    for (int i = 0; i < 3; i++) {
        std::cout << "a: "<< a << ", b size: " << testcases[i].size() << ", result: " << superPow(a, testcases[i]) << std::endl;
    }
}
