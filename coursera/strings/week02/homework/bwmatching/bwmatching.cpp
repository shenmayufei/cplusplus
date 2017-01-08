#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
  // initialize occ_count_before
  string charSet = "$ACGT";
  for(int i = 0; i < charSet.size(); i++) {
    occ_count_before[charSet[i]] = vector<int>(bwt.size()+1, 0);
  }

  char c = bwt[0];
  occ_count_before[c][1] = 1;

  for(int i = 1; i < bwt.size(); i++) {
    char c = bwt[i];

    // update occ_count_before according to bwt
    for(map<char, vector<int> >::iterator vIt = occ_count_before.begin(); vIt != occ_count_before.end(); vIt++) {
      if (vIt->first == bwt[i]) vIt->second[i+1] = vIt->second[i] + 1;
      else vIt->second[i+1] = vIt->second[i];
    }
  }
  // for(map<char, vector<int> >::iterator vIt = occ_count_before.begin(); vIt != occ_count_before.end(); vIt++) {
  //   std::cout << "char: " << vIt->first << ": ";
  //   for(int i = 0; i < vIt->second.size(); i++) {
  //     std::cout << vIt->second[i] << ", ";
  //   }
  //   std::cout << std::endl;
  // }

  string sorted = bwt;
  std::sort(sorted.begin(), sorted.end(), std::less<char>());
  for(int i = 0; i < sorted.size(); i++) {
    map<char, int>::const_iterator it = starts.find(sorted[i]);
    if (it == starts.end()) starts[sorted[i]] = i;
  }
  // std::cout << "source: " << bwt << std::endl;
  // std::cout << "sorted: " << sorted << std::endl << std::endl;
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char, int>& starts, 
                     const map<char, vector<int> >& occ_count_before) {
  int top = 0;
  int bottom = bwt.size() - 1;
  int ptIndex = pattern.size() - 1;
  while(top <= bottom) {
    if (ptIndex < 0) return bottom - top + 1;

    char lastLetter = pattern[ptIndex--];
    // std::cout << "pattern:" << pattern << ", index:" << ptIndex << std::endl;
    map<char, int>::const_iterator firstOccIt = starts.find(lastLetter);
    if (firstOccIt == starts.end()) return 0;
    map<char, vector<int> >::const_iterator vecIt = occ_count_before.find(lastLetter);
    const vector<int>& vec = vecIt->second;
    // std::cout << "top :" << top << ", bottom:" << bottom << ", first occur:" << firstOccIt->second << ", count[top]:" << vec[top] << ", count[bottom]:" << vec[bottom] << std::endl;
    top = firstOccIt->second + vec[top];
    bottom = firstOccIt->second + vec[bottom+1] - 1;
    // std::cout << "top: " << top << ", bottom: " << bottom << std::endl;
  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
