#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int const Letters = 5;

struct Node {
  int startIndex;
  int length;
  Node* next[Letters];

  Node (): startIndex(-1) {
		std::fill(next, next + Letters, (Node*)0);
	}

  bool isLeaf() const {
    return (next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr && next[4] == nullptr);
  }
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
    case '$': return 4; break;
		default: assert (false); return -1;
	}
}

// Build a suffix tree of the string text
Node* BuildSuffixTree(const string& text) {
  Node* t = new Node();
  for(int i = 0; i < text.size(); i++) {
    Node* cur = t;
    int j = i;
    while(true) {
      int idx = letterToIndex(text[j]);
      // next pointer is null, create a leaf node
      if(cur->next[idx] == nullptr) {
        cur->next[idx] = new Node();
        cur = cur->next[idx];
        cur->startIndex = i;;
        cur->length = text.size() - j;
        break;
      }

      // next pointer is not null
      cur = cur->next[idx];
      int k = 0;
      bool isMatch = true;
      int startIdx = cur->isLeaf() ? text.size() - cur->length : cur->startIndex;
      while(k < cur->length && j < text.size()) {
        if(text[k + startIdx] != text[j]) {
          isMatch = false;
          break;
        }
        k++;
        j++;
      }
      if (k==cur->length)   // '$' ensures that the two sub string both end, or neither end
        break;
      if (isMatch == true) // matched current branch
        continue;

      // split
      Node* tmp = new Node();
      if (cur->isLeaf()) {
        tmp->startIndex = cur->startIndex;
        cur->startIndex = startIdx;
      } else {
        tmp->startIndex = startIdx + k;
      }
      tmp->length = cur->length - k;
      cur->length = k;
      cur->next[letterToIndex(text[startIdx+k])] = tmp;
      // cout << "cur start:" << cur->startIndex << ", length:" << cur->length << ", tmp start:" << tmp->startIndex << ", length:" << tmp->length << ", startidx:" << startIdx << ", k:" << k <<endl;
      // add new Node to the branch
      int newNodeIdx = letterToIndex(text[j]);
      cur->next[newNodeIdx] = new Node();
      cur = cur->next[newNodeIdx];
      cur->startIndex = i;
      cur->length = text.size() - j;
      break;
    }
  }
  return t;
}

void ComputeEdges(const string& text, const Node* const t, vector<string>& edges) {
  if (t == nullptr) return;
  // cout << "start:" << t->startIndex << ", length:" << t->length << ", isleaf:" << t->isLeaf() << endl;
  if (t->isLeaf()) {
    edges.push_back(text.substr(text.size() - t->length, t->length));
  } else {
    edges.push_back(text.substr(t->startIndex, t->length));
    for(int i = 0; i < Letters; i++) {
      ComputeEdges(text, t->next[i], edges);
    }
  }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  // build suffix tree
  Node* t = BuildSuffixTree(text);
  vector<string> result;
  for(int i = 0; i < Letters; i++) ComputeEdges(text, t->next[i], result);
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
