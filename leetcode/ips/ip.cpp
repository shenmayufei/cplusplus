#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

bool isValid(string raw) {
  if (raw.size() > 3 || raw.size() == 0) return false;
  if (raw.size() != 1 && raw[0] == '0' ) return false;

  // length <3 && >0
  if (raw.size() < 3) return true;

  // length 3, check highest
  if (raw[0] > '2') return false;
  if (raw[0] == '1') return true;

  // highest is 2, check middle
  if (raw[1] < '5') return true;
  if (raw[1] > '5') return false;

  // middle is 5, check last
  if (raw[2] > '5') return false;
  return true;
}

vector< vector<string> >  parseIPHelper(vector<string> parts, string left) {
  vector<vector<string> > ret;
  if (parts.size() == 4 && left.size() > 0) return ret;

  int arrLen = left.size();
  // if left is 0, terminate the recursion
  if (arrLen == 0) {
    if (parts.size() != 4) return ret;
    ret.push_back(parts);
    return ret;
  }

  if (arrLen > 0) {
    vector<string> newParts(parts);
    newParts.push_back(left.substr(0, 1));
    auto ips = parseIPHelper(newParts, left.substr(1, arrLen-1));
    for(auto ip : ips) ret.push_back(ip);
  }
  if (arrLen > 1 && left[0] != '0') {
    vector<string> newParts(parts);
    newParts.push_back(left.substr(0, 2));
    auto ips = parseIPHelper(newParts, left.substr(2, arrLen-2));
    for(auto ip: ips) ret.push_back(ip);
  }
  if (arrLen > 2 && (left[0] == '1' || left[0] == '2')) {
    string tmp = left.substr(0, 3);
    if (isValid(tmp) == true) {
      vector<string> newParts(parts);
      newParts.push_back(left.substr(0, 3));
      auto ips = parseIPHelper(newParts, left.substr(3, arrLen-3));
      for(auto ip: ips) ret.push_back(ip);
    }
  }
  return ret;
}

vector<string> parseIPs(string raw) {
  if (raw.size() < 4) return vector<string>();
  auto ret = parseIPHelper(vector<string>(), raw);
  vector<string> ips;
  for (auto v : ret) {
    ips.push_back(v[0] + "." + v[1] + "." + v[2] + "." + v[3]);
  }
  return ips;
}

int main() {
  string str;
  std::cout << "Input a valid ip without dot: \n";
  std::cin >> str;
  auto ips = parseIPs(str);
  std::cout << "[";
  for (int i = 0; i < ips.size()-1; i++) {
    std::cout << "\"" << ips[i] << "\", ";
  }
  std::cout << "\"" << ips[ips.size()-1] << "\"]\n";
}
