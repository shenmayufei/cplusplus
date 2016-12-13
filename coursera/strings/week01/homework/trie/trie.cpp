#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  int nextIdx = 1; // every increment corresponding to a new node(increment of trie vector)
  for(vector<string>::const_iterator pt = patterns.begin(); pt != patterns.end(); pt++) {
    int bidx = 0; // the index of previous node
    for(int i = 0; i < pt->size(); i++) {
//      std::cout << "t.size():" << t.size() << "pt:" << *pt << ", i:" << i << ", bidx:" << bidx << ", next:" << nextIdx << std::endl;
      char c = (*pt)[i];
      if (t.size() == bidx) {
        edges ed;
        ed[c] = nextIdx++;
        t.push_back(ed);
        // switch bidx as ed[c]'s value
        bidx = ed[c];
      } else {
        edges& ed = t[bidx];
        map<char, int>::const_iterator it = ed.find(c);
        if (it == ed.end()) {
          ed[c] = nextIdx++;
          t.push_back(edges());
        }
        // switch bidx as ed[c]'s value
        bidx = ed[c];
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
