#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

//! @return the length of the longest substring without 
//!         repeating characters of a given string s.
//! @author Nhut Nguyen
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> position;
    int maxLen = 0;
    int start = -1;
    for (int i = 0; i < s.length(); i++) {
        auto it = position.find(s.at(i));
        if (it != position.end()) {
            start = max(start, it->second);
            it->second = i;
        } else {
            position.insert({s.at(i), i});
        }
        maxLen = max(maxLen, i - start);
    }
    return maxLen;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << lengthOfLongestSubstring("bbbbb") << endl;
    cout << lengthOfLongestSubstring("pwwkew") << endl;
}