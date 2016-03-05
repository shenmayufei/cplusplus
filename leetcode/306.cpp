/** 
 * 306. Additive Number
 * 2016 Jan 17th
 * note: compile it with --std=c++11 ( initializer_list http://www.cplusplus.com/reference/initializer_list/initializer_list/ )
 *
 * how to solve it: 
 *   1. divide string num into  a[0], a[1], a[2], ..., a[n-1] theoritically
 *      a. ==> len(a[n-1]) <= 1/2 * num.length()
 *      b. ==> len(a[i]) == len(a[i-1]) || len(a[i] = len(a[i-])+1, for any i (i < n && i > 0)
 *      c. according to rule a and b, we shall sheck if there is a i,j,k, which ensures num[k, n) - num[j, k) == num[i, j)
 *   2. sub functions 
 *      a. write a minus and check function, if check fails, return false
**/
#include <iostream>

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int numBits = num.length();

    }
};