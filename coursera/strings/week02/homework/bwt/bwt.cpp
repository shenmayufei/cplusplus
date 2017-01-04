#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  vector<string> strArr;
  int arrLen = text.size();
  strArr.reserve(arrLen);
  for(int i = 0; i < arrLen; i++) {
    strArr.push_back(text.substr(i, string::npos) + text.substr(0, i));
  }
  std::stable_sort(strArr.begin(), strArr.end(), std::less<string>());

  string result;
  result.reserve(arrLen);

  for(int i = 0; i < strArr.size() ; i++) {
    // cout << strArr[i] << endl;
    result.push_back(strArr[i][arrLen-1]);
  }
  
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}