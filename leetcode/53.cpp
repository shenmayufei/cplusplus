/*  53. Maximum Subarray
 *  
 *  Find the contiguous subarray within an array (containing at least one number)
 *  which has the largest sum.
 *
 *  For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 *  the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 */

#include <iostream>
#include <vector>
#include <limits>

using std::vector;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int total = nums[0];
        int max = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            if (total < 0) {
                total = nums[i];
            } else{
                total += nums[i];
            }
            if (total > max) max = total;
        }
        return max;
    }
};

void printVector(const vector<int>& vec) {
    std::cout << "[";
    for (vector<int>::const_iterator it=vec.begin(); it!=vec.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << ']';
}

int main() {
    Solution sol;

    vector< vector<int> > testcases;
    testcases.push_back(vector<int> {-2,1,-3,4,-1,2,1,-5,4});
    testcases.push_back(vector<int> {1,2,3});
    testcases.push_back(vector<int> {-1,-2,-3});
    testcases.push_back(vector<int> {-2,1});
    testcases.push_back(vector<int> {-2,-1, -3});
    
    for (int i = 0; i < testcases.size(); i++) {
        std::cout << i << ". Input: ";
        printVector(testcases[i]);
        std::cout << "; Output: " << sol.maxSubArray(testcases[i]) << std::endl;
    }
}