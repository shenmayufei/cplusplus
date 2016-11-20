#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using std::vector;
using std::pair;



double clustering(vector<int> x, vector<int> y, int k) {
  int vSize = x.size();
  if (vSize < k) return -1.0;
  if (vSize == k) return 0.0; // check 

  // initialize distances between any two points
  vector< vector<double> > cost(vSize, vector<double>(vSize, 0.0));
  for(int i = 0; i < vSize; i++) {
    for(int j = i+1; j < vSize; j++) {
      cost[i][j] = cost[j][i] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
    }
  }

  // @TODO: implementing idea

  vector<int> dset(vSize, 0);

  //write your code here
  return -1.;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
