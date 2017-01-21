#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  int border = 0;
  string t = pattern + "$" + text;
  vector<int> s(t.size(), 0);
  for(int i = 1; i < t.size(); i++) {
    while(border > 0 && t[i] != t[border]) border = s[border-1];
    if (t[i] != t[border]) border = 0;
    else border += 1;
    s[i] = border;
  }

  vector<int> result;
  int smax = pattern.size();
  for(int i = smax+1; i < t.size(); i++) {
    if (smax == s[i]) result.push_back(i-smax*2);
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
