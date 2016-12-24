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
// six situations:
// 1. extend at leaf node
// 2. split and extend at leaf node
// 3. extend at non-leaf node
// 4. split and extend at non-leaf node
// 5. match at non-leaf node
// 6. match at leaf node
Node* BuildSuffixTree(const string& text) {
  Node* t = new Node();
  for(int i = 0; i < text.size(); i++) {
    Node* cur = t;
    int j = i;
    while(true) {
      int idx = letterToIndex(text[j]);
      // cout << "i:" << i << ", j:" << j << endl;
      // next pointer is null, create a leaf node
      // deal with 1 and 3
      if(cur->next[idx] == nullptr) {
        // cout << "just iterate, i:" << i << ", j:" << j << ", start:" << cur->startIndex << ", length:" << cur->length << ", " << std::hex << cur << endl;
        cur->next[idx] = new Node();
        cur = cur->next[idx];
        cur->startIndex = i;;
        cur->length = text.size() - j;
        // cout << "add, start:" << cur->startIndex << ", length:" << cur->length  << ", " << std::hex << cur << endl << endl;
        break;
      }

      // next pointer is not null
      Node* prev = cur;
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

      if (isMatch) {
        if (j == text.size()) break;
        else continue; // check match at next round
      } 
      // else not match because text[k + startIdx] != text[j]
      if (cur->isLeaf()) {
        // cout << "split leaf, i: " << i << ", j: " << j << ", length:" << cur->length << ", " << std::hex << cur << endl;
        // split cur Leaf Node to tmp and cur
        Node* tmp = new Node();
        tmp->startIndex = startIdx;
        tmp->length = k;
        prev->next[letterToIndex(text[startIdx])] = tmp;
        cur->length -= k;
        tmp->next[letterToIndex(text[startIdx+k])] = cur;
        // cout << "result start:" << tmp->startIndex << ", length:" << tmp->length  << ", addr:" << std::hex << tmp << "; cur start:" << cur->startIndex << ", length:" << cur->length << ", addr:" << cur << endl;
        // add new Node to tmp
        int newIdx = letterToIndex(text[j]);
        tmp->next[newIdx] = new Node();
        tmp = tmp->next[newIdx];
        tmp->startIndex = i;
        tmp->length = text.size() - j;
        // cout << "add, start:" << tmp->startIndex << ", length:" << tmp->length  << ", isleaf:" << tmp->isLeaf() << ", " << std::hex << tmp << endl << endl;
      } else {
        // cout << "split node, i: " << i << ", j: " << j << ", start:" << cur->startIndex << ", length:" << cur->length << ", " << std::hex << cur << endl;
        // split cur Node to tmp and cur
        Node* tmp = new Node();
        tmp->startIndex = cur->startIndex;
        tmp->length = k;
        prev->next[letterToIndex(text[tmp->startIndex])] = tmp;
        cur->startIndex += k;
        cur->length -= k;
        tmp->next[letterToIndex(text[cur->startIndex])] = cur;
        // cout << "result start:" << tmp->startIndex << ", length:" << tmp->length  << ", addr:" << std::hex << tmp << "; cur start:" << cur->startIndex << ", length:" << cur->length << ", addr:" << cur << endl;
        // add new Node to tmp
        int newIdx = letterToIndex(text[j]);
        tmp->next[newIdx] = new Node();
        tmp = tmp->next[newIdx];
        tmp->startIndex = i;
        tmp->length = text.size() - j;
        // cout << "add, start:" << tmp->startIndex << ", length:" << tmp->length  << ", isleaf:" << tmp->isLeaf() << ", " << std::hex << tmp << endl << endl;
      }
      break;
    }
  }
  return t;
}

void DestroySuffixTree(Node* t) {
  if (t == nullptr) return;
  for(int i = 0; i < Letters; i++) {
    DestroySuffixTree(t->next[i]);
  }
  delete t;
}

void ComputeEdges(const string& text, const Node* const t, vector<string>& edges) {
  if (t == nullptr) return;
  // std::cout << "isLeaf:" << t->isLeaf() << ", start:" << t->startIndex << ", length:" << t->length << ", addr:" << std::hex << t << std::endl;
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
  DestroySuffixTree(t);
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
