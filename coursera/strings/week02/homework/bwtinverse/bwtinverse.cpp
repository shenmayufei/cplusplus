#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// struct Point is used to store letter information in a vector
struct Point {
  char elem;
  int globalIndex;
  Point(char elem, int gIndex) : elem(elem),globalIndex(gIndex) {};
  friend bool operator<(const Point& x, const Point& y) {
    if (x.elem < y.elem) return true;
    else if (x.elem > y.elem) return false;
    if (x.globalIndex < y.globalIndex) return true;
    return false;
  }
};

string InverseBWT(const string& bwt) {
  vector<Point> firstCol;
  firstCol.reserve(bwt.size());

  for(int i = 0; i < bwt.size(); i++) {
    firstCol.push_back(Point(bwt[i], i));
  }

  std::sort(firstCol.begin(), firstCol.end());

  // print log 
  // cout << "\nfirst col: \n";
  // for(int i = 0; i < firstCol.size(); i++) {
  //   cout << i << ": {" << firstCol[i].elem << ", " << firstCol[i].globalIndex << "}\n";
  // }
  // cout << endl;

  string text;  // store the result
  text.reserve(bwt.size());

  int nextIndex = firstCol[0].globalIndex;

  while(nextIndex != 0) {
    const Point& p = firstCol[nextIndex];
    text.push_back(p.elem);
    nextIndex = p.globalIndex;
  }
  text.push_back('$');

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
