/** 
 * 64. Minimum Path Sum My Submissions Question
 * 2016 Jan 14th
 * note: compile it with --std=c++11 ( initializer_list http://www.cplusplus.com/reference/initializer_list/initializer_list/ )
**/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSumRecursion(vector< vector<int> > & grid) {
        // special case: empty matrix
        if (grid.size()==0 || grid[0].size()==0) return 0;
        // normal matrix
        return minPathSumHelper(grid, grid[0].size(), grid.size(), 0, 0);
    }
    
    int minPathSumHelper(vector< vector<int> >& grid, int width, int height, int windex, int hindex) {
        if (windex == width-1 && hindex == height-1) return grid[hindex][windex];
        if (windex == width-1) return minPathSumHelper(grid, width, height, windex, hindex+1) + grid[hindex][windex];
        if (hindex == height-1) return minPathSumHelper(grid, width, height, windex+1, hindex) + grid[hindex][windex];
        int widthMin = minPathSumHelper(grid, width, height, windex+1, hindex);
        int heightMin = minPathSumHelper(grid, width, height, windex, hindex+1);
        return (widthMin > heightMin ? heightMin : widthMin) + grid[hindex][windex];
    }

    int minPathSumIteration(vector< vector<int> > & grid) {
        // special case: empty matrix
        if (grid.size()==0 || grid[0].size()==0) return 0;
        // normal matrix
        int width = grid[0].size();
        int height = grid.size();
        for (int i = 1; i < width; i++) {
            grid[0][i] += grid[0][i-1];
        }
        for (int j = 1; j < height; j++) {
            grid[j][0] += grid[j-1][0];
        }
        for (int i = 1; i < width; i++) {
            for (int j = 1; j < height; j++) {
                grid[j][i] += (grid[j-1][i] > grid[j][i-1] ? grid[j][i-1]: grid[j-1][i]);
            }
        }
        return grid[height-1][width-1];
    }
};

int main(int argc, char **argv) {
    vector< vector<int> > testcase1 {{7,1,3,5,8,9,9,2,1,9,0,8,3,1,6,6,9,5},{9,5,9,4,0,4,8,8,9,5,7,3,6,6,6,9,1,6},{8,2,9,1,3,1,9,7,2,5,3,1,2,4,8,2,8,8},{6,7,9,8,4,8,3,0,4,0,9,6,6,0,0,5,1,4},{7,1,3,1,8,8,3,1,2,1,5,0,2,1,9,1,1,4},{9,5,4,3,5,6,1,3,6,4,9,7,0,8,0,3,9,9},{1,4,2,5,8,7,7,0,0,7,1,2,1,2,7,7,7,4},{3,9,7,9,5,8,9,5,6,9,8,8,0,1,4,2,8,2},{1,5,2,2,2,5,6,3,9,3,1,7,9,6,8,6,8,3},{5,7,8,3,8,8,3,9,9,8,1,9,2,5,4,7,7,7},{2,3,2,4,8,5,1,7,2,9,5,2,4,2,9,2,8,7},{0,1,6,1,1,0,0,6,5,4,3,4,3,7,9,6,1,9}};
    
    Solution sol;
    cout << "minPathSum: " << sol.minPathSumRecursion(testcase1) << endl;
}
