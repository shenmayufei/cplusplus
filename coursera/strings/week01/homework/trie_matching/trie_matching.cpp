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

	Node ()
	{
		fill (next, next + Letters, (Node*)0);
	}

	bool isLeaf () const
	{
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

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	// build trie tree 
	Node* t =  new Node();
	for(int i = 0; i < n; i++) {
		const string& ptn = patterns[i];
		Node* cur = t;
		for(int j = 0; j < ptn.size(); j++) {
			int idx = letterToIndex(ptn[j]);
			if (cur->next[idx] == nullptr) {
				cur->next[idx] = new Node();
			}
			cur = cur->next[idx];
		}
	}

	// match text to patterns
	vector <int> result;
	for(int i = 0; i < text.size(); i++) {
		Node* cur = t;
		bool isMatch = false;
		for(int j = i; j < text.size(); j++) {
			int idx = letterToIndex(text[j]); 
			if (cur->next[idx] == nullptr) {
				if(cur->isLeaf()) isMatch = true;
				break;
			}
			cur = cur->next[idx];
		}
		if (isMatch == true) {
			result.push_back(i);
		} else {
			if (cur->isLeaf()) {
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
