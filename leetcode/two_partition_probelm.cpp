// https://www.geeksforgeeks.org/partition-problem-dp-18/
#include <iostream>
#include <vector>
#include <numeric>

bool can_sum_up_to(const std::vector<long long>& xs, long long target) {
  std::vector<std::vector<bool>> table(target+1, std::vector<bool>(xs.size() + 1, false));
  std::cout << "size = " << target + 1 << "*" << xs.size() + 1 << std::endl;
  for(size_t j = 0; j < xs.size()+1; j++) table[0][j] = true;
  for(int i = 0; i < target; i++) {
    for(int j = 0; j < xs.size(); j++) {
      // std::cout << "i = " << i << ", j = " << j << " = " << table[i][j] << std::endl;
      if (table[i+1][j]) table[i+1][j+1] = true;
      else if (i+1-xs[j] >= 0 && table[i+1-xs[j]][j]) table[i+1][j+1] = true;
    }
  }
  for (size_t j = 0; j < xs.size() + 1; j++) {
    if (table[target][j]) return true;
  }
  return false;
}

bool can_partition_two(const std::vector<long long>& xs) {
  long long sum = std::accumulate(xs.begin(), xs.end(), 0LL);
  if (sum%2 == 1)  return false;
  else return can_sum_up_to(xs, sum/2);
}

int main() {
  std::vector<std::vector<long long>> xss = {
    {1, 5, 11, 5},
    {1, 2, 3, 3},
    {1, 3, 2}
  };

  std::vector<bool> expects = {true, false, true};
  for (size_t i = 0; i < xss.size(); i++) {
    bool got = can_partition_two(xss[i]);
    if (got != expects[i]) {
      std::cout << "Input: " << i << ", expect " << expects[i] << ", but got " << got << std::endl;
    }
  }
}