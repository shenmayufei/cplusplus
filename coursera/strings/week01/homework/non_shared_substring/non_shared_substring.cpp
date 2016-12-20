#include <iostream>
#include <string>
#include <cassert>

using namespace std;

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
      // cout << "i:" << i << ", j:" << j << endl;
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
      // cout << "i: " << i << ", j:" << j << ", k:" << k << endl;
      if (j == text.size())   // j == text.size() => all letters in sub string matches
        break;
			
			// sub string does not finish, "cur" finishes
      if (isMatch == true) {
				// match all letters in "cur" Node, but text not finish yet
				if (cur->isLeaf()) { 
					// cur->isLeaf() => extend length is ok, no need to create a new Node
					cur->length += text.size() - j;
					break;
				} else {
					continue;
				}
			}

      // does not match, split "cur" Node, and add a new leaf to it
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
      // cout << "cur start:" << cur->startIndex << ", length:" << cur->length << ", tmp start:" << tmp->startIndex << ", length:" << tmp->length << ", startidx:" << startIdx << ", k:" << k << ", j:" << j<<endl;
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

bool isMatch(Node* t, const string& src, const string& pattern, int start, int length) {
	if( t == nullptr) return false;
	Node* cur = t;
	int incr = 0;
	while(true) {
		int idx = letterToIndex(pattern[start + incr]);
		if (cur->next[idx] == nullptr) {
			return false;
		}
		cur = cur->next[idx];
		
		int curStart = cur->startIndex;
		if (cur->isLeaf()) {
			curStart = src.size() - cur->length;
		}
		int curIncr = 0;
		while(incr < length && curIncr < cur->length) {
			if (pattern[start + incr] != src[curStart + curIncr]) return false;
			incr++;
			curIncr++;
		}
		if (incr == length) return true;
	}
	return true;
}

string solve (string p, string q)
{
	Node* tree = BuildSuffixTree(q);
	int start = 0;
	int length = 1;
	for(int len = 1; len < p.size(); len++) {
		for(int startIdx = 0; startIdx < p.size() - len; startIdx++) {
			if (isMatch(tree, q, p, startIdx, len) == false) return p.substr(startIdx, len);
		}
	}

	return "";
}

int main (void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve (p, q);

	cout << ans << endl;

	return 0;
}
