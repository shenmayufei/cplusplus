#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

bool isLess (Segment i, Segment j) { return (i.start<j.start); }

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;

  std::sort(segments.begin(), segments.end(), isLess);

  size_t i = 0;
  while ( i < segments.size()) {
    Segment seg = segments[i];
    size_t j = i+1;
    while ( j < segments.size()) {
      if (segments[j].start <= seg.end) {
        if (segments[j].end < seg.end) {
          seg.end = segments[j].end;
        }
        if (segments[j].start > seg.start) {
          seg.start = segments[j].start;
        }
      } else if(segments[j].start > seg.end) {
        points.push_back(seg.end);
        i = j;
        break;
      }
      j++;
    }

    if (j == segments.size()) {
      points.push_back(seg.end);
      return points;
    }
  }

  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
