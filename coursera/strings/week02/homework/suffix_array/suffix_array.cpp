#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

struct Rotation {
  string str;
  int start;
  Rotation(const string& src, int rotate): start(rotate) {
    str = src.substr(rotate, string::npos) + src.substr(0, rotate);
  }
  friend bool operator<(const Rotation& r1, const Rotation& r2) {
    return r1.str < r2.str;
  }
};

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<Rotation> rotations;
  rotations.reserve(text.size());
  for(int i = 0; i < text.size(); i++) {
    rotations.push_back(Rotation(text, i));
  }
  std::stable_sort(rotations.begin(), rotations.end());
  vector<int> result;
  for(int i = 0; i < rotations.size(); i++) {
    result.push_back(rotations[i].start);
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
