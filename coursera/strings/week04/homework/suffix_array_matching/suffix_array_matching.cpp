#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::string;
using std::vector;

// ----------BuildSuffixArray----Start-----------------------------------------
// BuildSuffixArray and its helper functions
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
    count[indexOfChar(c)] --;
    order[count[indexOfChar(c)]] = i;
  }
  // for(int i = 0; i < arrLen; i++) cout << order[i] << ", ";
  // cout << endl;
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
// --------BuildSuffixArray----END---------------------------------------------


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  // std::cout << "enter" << std::endl;
  // firstIdxes array is used to store the index of the first occurence of certain
  // character in suffix_array, for fast query
  vector<int> counts(CharNumber, 0);
  for(int i = 0; i < suffix_array.size(); i++) counts[indexOfChar(text[suffix_array[i]])] ++;
  
  vector<int> firstIdxes(counts.begin(), counts.end());
  for(int j = 1; j < firstIdxes.size(); j++) {
    firstIdxes[j] += firstIdxes[j-1];
  }
  for(int j = firstIdxes.size() - 1; j > 0; j--) firstIdxes[j] = firstIdxes[j-1];
  firstIdxes[0] = 0;

  // std::cout << "step 1, finish get char counts and indexes\n";
  // std::cout << "suffix_array.size(): " << suffix_array.size() << std::endl;

  if (pattern.size() == 0) return vector<int>();
  char c = pattern[0];
  int idx = indexOfChar(c);
  int start = firstIdxes[idx];
  int end = firstIdxes[idx] + counts[idx];

  if (end-start == 0) return vector<int>();

  int arrLen = text.size();

  vector<int> result;
  for(int idx = start; idx < end; idx++) {
    int startIndex = suffix_array[idx];
    // std::cout << "start:" << start << ", end:" << end << ", idx: " << idx << ", start index:" << startIndex << std::endl;
    if (pattern.size() > arrLen + 1 - startIndex) continue;  // cannot be equal
    bool match = true;
    for(int i = 0; i < pattern.size(); i++) {
      if (text[startIndex + i] != pattern[i]) {
        match = false;
        break;
      }
    }
    if (match) result.push_back(startIndex);
  }

  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
