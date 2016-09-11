#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector< pair<int, long long> >  next_free_time;
    next_free_time.reserve(num_workers_);
    for(int i = 0; i < num_workers_; i++) next_free_time.push_back(make_pair(i, 0));

    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];

      assigned_workers_[i] = next_free_time[0].first;
      start_times_[i] = next_free_time[0].second;

      next_free_time[0].second += duration;
      // cout << "before: {" << next_free_time[0].first << ", " << next_free_time[0].second << "}\n";
      SiftDown(next_free_time, 0);
      // cout << "after : {" << next_free_time[0].first << ", " << next_free_time[0].second << "}\n\n";
    }
  }

  void SiftDown(vector< pair<int, long long> >& arr, int i) {
    int arrLen = arr.size();
    int minIdx = i;

    auto minP = arr[minIdx];

    int lc = 2 * i + 1;
    if (lc < arrLen) {
      if (arr[lc].second < minP.second) {
        minIdx = lc;
      } else if (arr[lc].second == minP.second) {
        if (arr[lc].first < minP.first) minIdx = lc;
      }
    }

    minP = arr[minIdx];

    int rc = 2 * i + 2;
    if (rc < arrLen ) {
      if (arr[rc].second < minP.second) {
        minIdx = rc;
      } else if (arr[rc].second == minP.second) {
        if (arr[rc].first < minP.first) {
          minIdx = rc;
        }
      }
    }

    if (minIdx != i) {  // exchange
      swap(arr[i], arr[minIdx]);
      SiftDown(arr, minIdx);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
