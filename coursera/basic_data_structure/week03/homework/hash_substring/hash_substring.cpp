#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>   /* rand() srand() */

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

bool isEqual(const string& text, const string& pattern, size_t start) {
    if(start + pattern.size() > text.size()) return false;
    for(size_t i = 0; i < pattern.size(); i++) {
        if (text[start+i] != pattern[i]) return false;
    }
    return true;
}

// polyHash return the hash code for a string [start, end)
ull ployHash(const string& text, size_t start, size_t end, ull p, ull x) {
    ull hash = 0
    for (size_t i = end-1; i >= start; i--) {
        hash = (hash * x + text[i]) % p;
    }
    return hash
}

std::vector<int> precompute(const string& text, int len, ull p, ull x) {
    int resLen = text.size()-len+1;
    if (resLen < 1) return std::vector<int>();

    // allocate memory for precomputed data
    std::vector<int> result(resLen, 0);
    result[resLen-1] = polyHash(text, resLen-1-len, resLen, p, x);

    // y = x^len
    ull y = 1;
    for (size_t i = 0; i < len; i++) {
        y*=x;
    }

    for (size_t i = resLen-2; i>=0; i--) {
        result[i] = (x * result[i+1] + text[i] - y * text[i+len]) % p;
    }
    return result;
}

std::vector<int> get_occurrences_fast(const Data& input) {
    static const ull p = 1000000007;
    static const ull x = rand() % (prime-1) + 1;
    std::vector<int> result;

    ull pHash = polyHash(input.pattern, 0, input.pattern.size(), p, x);
    std::vector<int> hashedArr = precompute(input.text, input.pattern.size(), p, x);
    for (std::vector<int>::const_iterator it = hashedArr.begin(); it != hashedArr.end(); it++) {
        if (pHash != *it) continue;
        if (isEqual(input.text, input.pattern, i) == false) continue;
        result.push(i); 
    }
    return result;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
