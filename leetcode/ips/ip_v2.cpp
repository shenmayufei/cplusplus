#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

string parseIP(const vector<int>& nums, int dot1, int dot2, int dot3) {
    int part1 = 0, part2 = 0, part3 = 0, part4 = 0;
    for(int i = 0; i < dot1; i++) {
        part1 *= 10;
        part1 += nums[i];
    }
    if (part1 < 0 || part1 > 255) return "";

    for(int i = dot1; i < dot2; i++) {
        part2 *= 10;
        part2 += nums[i];
    }
    if (part2 < 0|| part2 >255) return "";

    for(int i = dot2; i < dot3; i++) {
        part3 *= 10;
        part3 += nums[i];
    }
    if (part3 < 0 || part3 > 255)  return "";

    for(int i = dot3; i < nums.size(); i++) {
        part4 *= 10;
        part4 += nums[i];
    }
    if (part4 <0 || part4 > 255) return "";

    string ret(nums.size() + 3, '.');
    int j = 0;
    for(int i = 0; i < dot1; i++) ret[j++] = nums[i] + '0';
    ret[j++] = '.';
    for(int i = dot1; i < dot2; i++)  ret[j++] = nums[i] + '0';
    ret[j++] = '.';
    for(int i = dot2; i < dot3; i++) ret[j++] = nums[i] + '0';
    ret[j++] = '.';
    for(int i = dot3; i < nums.size(); i++) ret[j++] = nums[i] + '0';
    return ret;
}

vector<string> parseIPs(string src) {
    // prerequisite: length [4,12]
    if (src.size() < 4 || src.size() > 12) return vector<string>();

    // convert the string into integer array
    vector<int> nums(src.size(), 0);
    for(int i =0; i < src.size(); i++) {
        nums[i] = src[i] - '0';
    }

    vector<string> ret;

    // iterate all possibilities
    int dot1, dot2, dot3; // dot index to separate numbers
    int numSize = nums.size();
    for(dot1 = 1; dot1 < numSize-2; dot1 ++) { // possible locations of first dot
        for(dot2 = dot1 + 1; dot2 < numSize-1 && dot2 <= dot1 + 3; dot2++) {  // possible locations of second dot
            for(dot3 = dot2+1; dot3 < numSize && dot3 >= numSize-3 && dot3 <= dot2 + 3 ; dot3++) { // possible locations of third dot
                string str = parseIP(nums, dot1, dot2, dot3);
                if (str.size() > 0) ret.push_back(str);
            }
        }
    }

    return ret;
}

int main() {
  string str;
  std::cout << "Input a valid ip without dot: \n";
  std::cin >> str;
  const vector<string>& ips = parseIPs(str);
  std::cout << "[";
  for (int i = 0; i < ips.size()-1; i++) {
    std::cout << "\"" << ips[i] << "\", ";
  }
  std::cout << "\"" << ips[ips.size()-1] << "\"]\n";
}
