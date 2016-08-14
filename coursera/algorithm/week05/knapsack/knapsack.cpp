#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}


int optimal_weight_my(int W, const vector<int> &w) {
  //write your code here
  vector<vector<int> > wMap;
  wMap.reserve(W+1);
  for(int i = 0; i < W+1; i++){
    wMap[i].reserve(w.size()+1);
    wMap[i].push_back(0);
  }

  for (int i = 0; i <= w.size(); i++) {
    wMap[0][i] = 0;
  }

  for (int i = 1; i <= w.size() ;i++) {
    for (int j = 1; j <= W; j++) {
      wMap[j][i] = wMap[j][i-1];
      if (w[i-1] <= j) {
        int val = wMap[j-w[i-1]][i-1] + w[i-1];
        if (val > wMap[j][i]) {
          wMap[j][i] = val;
        }
      }
    }
  }

  return wMap[W][w.size()];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight_my(W, w) << '\n';
}
