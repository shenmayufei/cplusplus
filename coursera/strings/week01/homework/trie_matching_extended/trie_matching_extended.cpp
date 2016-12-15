#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;

struct Node
{
	Node* next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, (Node*)0);
		patternEnd = false;
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

vector <int> solve (string text, int n, const vector<string>& patterns)
{
	// build trie tree 
	Node* t = new Node();
	for(int i = 0; i < n; i++) {
		const string& ptn = patterns[i];
		const int maxIdx = ptn.size()-1;
		Node* cur = t;
		for(int j = 0; j < maxIdx; j++) {
			int idx = letterToIndex(ptn[j]);
			if (cur->next[idx] == nullptr) {
				cur->next[idx] = new Node();
			}
			cur = cur->next[idx];
		}
		int idx = letterToIndex(ptn[maxIdx]);
		if(cur->next[idx] == nullptr) {
			cur->next[idx] = new Node();
		}
		cur = cur->next[idx];
		cur->patternEnd = true;
	}

	// match text to patterns
	vector <int> result;
	for(int i = 0; i < text.size(); i++) {
		Node* cur = t;
		bool isMatch = false;
		for(int j = i; j < text.size(); j++) {
			if(cur->patternEnd) {
				isMatch = true;
				break;
			}
			int idx = letterToIndex(text[j]); 
			if(cur->next[idx] == nullptr) {
				break;  // not match
			}
			cur = cur->next[idx];

		}
		if (isMatch == true) {
			result.push_back(i);
		} else {
			if (cur->patternEnd) {
				// special case: pattern and text are of the same length and matches
				result.push_back(i);
			}
		}
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
