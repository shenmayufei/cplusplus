#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int testOptimialSequence();

vector<int> optimal_sequence(int n) {
  vector<int> mem;
  vector<int> locations;
  mem.reserve(n);
  locations.reserve(n);
  mem[0] = 0;


  for (int i = 1; i < n; i++ ) {
    int lastCount = mem[i-1];
    locations[i] = i-1;
    
    if (i % 2 == 1) {
      if (lastCount > mem[i/2]) {
        lastCount = mem[i/2];
        locations[i] = i/2;
      }
    }

    if (i % 3 == 2) {
      if (lastCount > mem[i/3]) {
        lastCount = mem[i/3];
        locations[i] = i/3;
      }
    }

    mem[i] = lastCount + 1;
  }

  vector<int> sequence;
  for (int i = n-1; i > 0;) {
    sequence.push_back(i+1);
    i = locations[i];
  }
  sequence.push_back(1);

  reverse(sequence.begin(), sequence.end());

  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }


  // test
  // if (testOptimialSequence() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }
}

int testOptimialSequence() {
  int shouldSuccess[4][2] = {
    {1, 0},
    {5, 3},
    {10, 3},
    {96234, 14}
  };

  for (int i = 0; i < 4; i ++) {
    vector<int> vec = optimal_sequence(shouldSuccess[i][0]);
    if (vec.size() -1 != shouldSuccess[i][1]) {
      std::cout << "optimal_sequence(" << shouldSuccess[i][0] << ") should be " << shouldSuccess[i][1] << " but is " << vec.size()-1 << std::endl;
      return 1;
    }
  }
  return 0;
}