#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int const Letters = 4;

struct Node {
  int startIndex;
  int length;
  Node* next[Letters];

  Node (): startIndex(-1), length(0) {
		std::fill(next, next + Letters, (Node*)0);
	}

  bool isLeaf() const {
    return (next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr);
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
// six situations:
// 1. match at some node
// 2. extend at some node
// 3. split and extend at some node
Node* BuildSuffixTree(const string& text) {
  Node* t = new Node();
  for(int i = 0; i < text.size(); i++) {
    Node* cur = t;
    int j = i;
    while(true) {
      int idx = letterToIndex(text[j]);
      // 1. extend at some node
      if(cur->next[idx] == nullptr) {
        cur->next[idx] = new Node();
        cur = cur->next[idx];
        cur->startIndex = j;
        cur->length = text.size() - j;
        break;
      }

      // next pointer is not null
      Node* prev = cur;
      cur = cur->next[idx];
      int k = 0;
      bool isMatch = true;
      while(k < cur->length && j < text.size()) {
        if(text[k + cur->startIndex] != text[j]) {
          isMatch = false;
          break;
        }
        k++;
        j++;
      }
			
			// match
      if (isMatch == true) {
        if (j == text.size()) break;  // match to the end
        else continue;  // leave matching work to the next round
			}

      // does not match, split cur Node to tmp and cur
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
      tmp->startIndex = j;
      tmp->length = text.size() - j;
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

string getShortestNonShareString(const string& p, const string& q, const string& prefix, Node* pt, int pStart, Node* qt, int qStart) {
  if (pt == nullptr || pt->length == 0) {
    return "";  // match, so return empty string
  }
  if (qt == nullptr || qt->length == 0) {
    string result = prefix + p[pt->startIndex + pStart];
    // cout << "000 pt:" << std::hex << pt << ", start:" << pt->startIndex << ", length:" << pt->length << ", pstart:" << pStart << ", prefix: " << prefix << ", result:" << result << endl;
    return result;
  }
  assert(pStart < pt->length && qStart < qt->length); // ensure the prerequisite
  int pCur = pStart;
  int qCur = qStart;
  while(pCur < pt->length && qCur < qt->length) {
    if (p[pt->startIndex + pCur] != q[qt->startIndex + qCur]) {
      string result = prefix + p.substr(pt->startIndex + pStart, pCur - pStart+1);
      // cout << "001 pt:" << std::hex << pt << ", start:" << pt->startIndex << ", length:" << pt->length << ", pstart:" << pStart<< ", pCur:" << pCur << ", prefix: " << prefix << ", result:" << result << endl;
      return result;
    }
    pCur++;
    qCur++;
  }
  
  string newPrefix = prefix + p.substr(pt->startIndex + pStart, pCur - pStart);
  if (pCur == pt->length) {
    string result;
    if (qCur == qt->length ) {  // both pt and qt ends
      for(int i = 0; i < Letters; i++) {
        string tmp = getShortestNonShareString(p, q, newPrefix, pt->next[i], 0, qt->next[i], 0);
        if (tmp.size() == 0) continue;
        if (result.size() == 0) result = tmp;
        else if (tmp.size() < result.size()) result = tmp;
      }
      // cout << "002.1 pt:" << std::hex << pt << ", start:" << pt->startIndex << ", length:" << pt->length << ", pstart:" << pStart<< ", pCur:" << pCur << ", new prefix: " << newPrefix << ", result:" << result << endl;
    } else { // current pt ends, but qt not
      for(int i = 0; i < Letters; i++) {
        string tmp = getShortestNonShareString(p, q, newPrefix, pt->next[i], 0, qt, qCur);
        if (tmp.size() == 0) continue;
        if (result.size() == 0) result = tmp;
        else if (tmp.size() < result.size()) result = tmp;
      }
      // cout << "002.2 pt:" << std::hex << pt << ", start:" << pt->startIndex << ", length:" << pt->length << ", pstart:" << pStart<< ", pCur:" << pCur << ", new prefix: " << newPrefix << ", result:" << result << endl;
    }

    return result;
  }

  // qt ends, but pt not
  int nextCharIndex = letterToIndex(p[pt->startIndex + pCur]);
  string result = getShortestNonShareString(p, q, newPrefix, pt, pCur, qt->next[nextCharIndex], 0);
  // cout << "003 pt:" << std::hex << pt << ", start:" << pt->startIndex << ", length:" << pt->length << ", pstart:" << pStart<< ", pCur:" << pCur << ", new prefix: " << newPrefix << ", result:" << result << endl;
  return result;
}

string solve (string p, string q)
{
  Node* pt = BuildSuffixTree(p);
	Node* qt = BuildSuffixTree(q);

  string result;
  for(int i = 0; i < Letters; i++) {
    string tmp = getShortestNonShareString(p, q, "", pt->next[i], 0, qt->next[i], 0);
    if (tmp.size() == 0) continue;
    if (result.size() == 0) result = tmp;
    else if (tmp.size() < result.size()) result = tmp;
  }
  
  DestroySuffixTree(pt);
  DestroySuffixTree(qt);
	return result;
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
