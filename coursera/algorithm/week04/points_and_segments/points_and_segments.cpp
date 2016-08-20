#include <iostream>
#include <vector>
#include <ctime>

using std::vector;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  //write your code here
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int test() {
  while(true) {
    size_t sSize = rand() + 20000 + 1;
    size_t pSize = rand() + 20000 + 1;

    vector<int> starts, ends, points;

    for(size_t i = 0; i < sSize; i++) {
      int start = rand();
      starts.push_back(start);
      ends.push_back(start + rand());
    }

    for(size_t i = 0; i < pSize; i++) {
      points.push_back(rand());
    }

    clock_t t, t1, t2;

    t = clock();
    vector<int> slowRes = naive_count_segments(starts, ends, points);
    t1 = clock();
    vector<int> fastRes = naive_count_segments(starts, ends, points);
    t2 = clock();

    t2 = t2 - t1;
    t1 = t1 -t;
    printf ("slow version cost %lu clicks (%f milli seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC * 1000);
    printf ("fast version cost %lu clicks (%f milli seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC * 1000);
    std::cout << std::endl;
  }

  return 0;
}


int main() {
  // int n, m;
  // std::cin >> n >> m;
  // vector<int> starts(n), ends(n);
  // for (size_t i = 0; i < starts.size(); i++) {
  //   std::cin >> starts[i] >> ends[i];
  // }
  // vector<int> points(m);
  // for (size_t i = 0; i < points.size(); i++) {
  //   std::cin >> points[i];
  // }
  // //use fast_count_segments
  // vector<int> cnt = naive_count_segments(starts, ends, points);
  // for (size_t i = 0; i < cnt.size(); i++) {
  //   std::cout << cnt[i] << ' ';
  // }

  if(test() != 0) {
    std::cout << "test fails" << std::endl;
  }
}
