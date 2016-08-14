#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
  if (str1.size() == 0) return str2.size();
  if (str2.size() == 0) return str1.size();

  vector< vector<int> > distMap;
  distMap.reserve(str1.size());
  for (int i = 0; i < str1.size(); i++) {
    distMap[i].reserve(str1.size());
  }

  // init first col and row of the distance map
  if (str1[0] == str2[0]) {
    distMap[0][0] = 0;
  } else {
    distMap[0][0] = 1;
  }

  for(int i = 1; i < str1.size(); i++) {
    distMap[i][0] = distMap[i-1][0];

    if (distMap[i-1][0] == i-1) {  // str2[0] has already been matched
      distMap[i][0]++;
    } else if (str1[i] != str2[0]) { // str2[0] has not been matched, and does not match for this time
      distMap[i][0]++;
    }
  }

  for(int i = 1; i < str2.size(); i++) {
    distMap[0][i] = distMap[0][i-1];

    if (distMap[0][i-1] == i-1) {  // str1[0] has already been matched
      distMap[0][i]++;
    } else if (str2[i] != str1[0]) { // str1[0] has not been matched, and does not match for this time
      distMap[0][i]++;
    }
  }

  // after initialization, start calculation
  for (int i = 1; i < str1.size(); i++) {
    for (int j = 1; j < str2.size(); j++) {
      int val = distMap[i-1][j] + 1;  // insertion

      if (val > distMap[i][j-1] + 1) {// deletion
        val = distMap[i][j-1] + 1; 
      }
      if (str1[i] == str2[j]) {       // match
        if (val > distMap[i-1][j-1]) val = distMap[i-1][j-1];
      } else {                        // mismatch
        if (val > distMap[i-1][j-1]) val = distMap[i-1][j-1] + 1;
      }

      distMap[i][j] = val;
      // std::cout << "loop j = " << j << ", val:" << val << std::endl;
    }
    // std::cout << "loop i = " << i << std::endl;
  }

  return distMap[str1.size()-1][str2.size()-1];
}


int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
