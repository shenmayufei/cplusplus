#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void siftDown(int i) {
    int arrLen = data_.size();
    int minIdx = i;
    int lc = 2 * i + 1;
    if (lc < arrLen && data_[lc] < data_[minIdx]) {
      minIdx = lc;
    }
    int rc = 2 * i + 2;
    if (rc < arrLen && data_[rc] < data_[minIdx]) {
      minIdx = rc;
    }

    if (minIdx != i) {  // exchange
      swap(data_[i], data_[minIdx]);
      swaps_.push_back(make_pair(i, minIdx));
      siftDown(minIdx);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    int arrLen = data_.size();
    for (int i = arrLen -1; i >= 0; i--) {
      siftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
