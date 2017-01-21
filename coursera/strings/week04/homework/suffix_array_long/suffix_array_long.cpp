#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

const int CharNumber = 5;

int indexOfChar(char c) {
  switch(c) {
    case '$':
      return 0;
    case 'A':
      return 1;
    case 'C':
      return 2;
    case 'G':
      return 3;
    case 'T':
      return 4;
    default:
      assert (false); return -1;
  }
}

vector<int> SortCharacters(const string& text) {
  int arrLen = text.size();
  vector<int> order(arrLen, 0);
  vector<int> count(CharNumber, 0);
  for(int i = 0; i < arrLen; i++) count[indexOfChar(text[i])] ++;
  for(int j = 1; j < CharNumber; j++) count[j] += count[j-1];
  for(int i = arrLen - 1; i >= 0; i--) {
    char c = text[i];
    count[c] --;
    order[count[c]] = i;
  }
  return order;
}

vector<int> ComputeCharClasses(const string& text, const vector<int>& order) {
  int arrLen = text.size();
  vector<int> cl(arrLen, 0);
  for(int i = 1; i < arrLen; i++) {
    if(text[order[i]] != text[order[i-1]]) {
      cl[order[i]] = cl[order[i-1]] + 1;
    } else {
      cl[order[i]] = cl[order[i-1]];
    }
  }
  return cl;
}

vector<int> SortDoubled(const string& text, int L, const vector<int>& order, const vector<int>& cl) {
  int arrLen = text.size();
  vector<int> count(arrLen, 0);
  vector<int> newOrder(arrLen, 0);
  for(int i = 0; i < arrLen; i++) {
    count[cl[i]] += 1;
  }

  for(int j = 1; j < arrLen; j++) {
    count[j] += count[j-1];
  }

  for(int i = arrLen-1; i >= 0; i--) {
    int start = (order[i] - L + arrLen) % arrLen;
    int clVal = cl[start];
    count[clVal] -= 1;
    newOrder[count[clVal]] = start;
  }
  return newOrder;
}

vector<int> UpdateClasses(const vector<int>& order, const vector<int>& cl, int L) {
  int arrLen = order.size();
  vector<int> newCl(arrLen,0);
  newCl[order[0]] = 0;
  for(int i = 1; i < arrLen; i++) {
    int cur = order[i];
    int prev = order[i-1];
    int mid = (cur + L) % arrLen;
    int midPrev = (prev + L) % arrLen;
    if (cl[cur] != cl[prev] || cl[mid] != cl[midPrev]) {
      newCl[cur] = newCl[prev] + 1;
    } else {
      newCl[cur] = newCl[prev];
    }
  }
  return newCl;
}


// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  vector<int> order = SortCharacters(text);
  vector<int> cl = ComputeCharClasses(text, order);
  int L = 1;
  while(L < text.size()) {
    order = SortDoubled(text, L, order, cl);
    cl = UpdateClasses(order, cl, L);
    L *= 2;
  }
  return order;
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
