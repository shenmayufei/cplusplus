/*  368. Largest Divisible Subset
 *  
 *  Given a set of distinct positive integers, find the largest subset 
 *  such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
 *  If there are multiple solutions, return any subset is fine.
 *
 *  Compile: g++ -o main 386.cpp -lm --std=c++11
 *  Run:     ./main
 *
 *  Example 1:
    nums: [1,2,3]
    Result: [1,2] (of course, [1,3] will also be ok)
 *
 *
 *  Example 2:
    nums: [1,2,4,8]
    Result: [1,2,4,8]
 */

#include <iostream>
#include <vector>
#include <algorithm>    // std::reverse

using std::vector;

class Solution {
public:
    struct Node {
        int count;
        int prev;
        Node(int count, int prev): count(count), prev(prev){}
    };

    // Greedy
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if (nums.size() == 0) return vector<int>{};
        std::sort(nums.begin(), nums.end());  // sort it first
        vector<Node> summary(nums.size(), Node(-1, -1));
        for(int i = 1; i < nums.size(); i++) {
            for(int j = i-1; j>=0;j--) {
                if (nums[i] % nums[j] == 0 && summary[i].count < summary[j].count+1) {
                    summary[i].count = summary[j].count+1;
                    summary[i].prev = j;
                }
            }
        }

        int end = 0;
        for(int i = 1; i < summary.size(); i++) {
            if (summary[i].count > summary[end].count) end = i;
        }

        vector<int> ret;
        while(end != -1) {
            ret.push_back(nums[end]);
            end = summary[end].prev;
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
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
    testcases.push_back(vector<int> {});
    testcases.push_back(vector<int> {1,2,3});
    testcases.push_back(vector<int> {1,2,4,8});
    testcases.push_back(vector<int> {3,4,16,8}); // need to sort
    
    for (int i = 0; i < testcases.size(); i++) {
        std::cout << i << ". Input: ";
        printVector(testcases[i]);
        std::cout << "; Output: ";
        printVector(sol.largestDivisibleSubset(testcases[i]));
        std::cout << std::endl;
    }
}