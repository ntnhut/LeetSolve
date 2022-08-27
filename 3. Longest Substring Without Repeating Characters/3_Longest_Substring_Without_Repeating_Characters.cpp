#include <iostream>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> position;
    int maxLen = 0;
    int start = -1;
    for (int i = 0; i < s.length(); i++) {
        if (position.find(s[i]) != position.end()) {
            start = max(start, position[s[i]]);
        }
        position[s[i]] = i;
        maxLen = max(maxLen, i - start);
    }
    return maxLen;
}

int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << lengthOfLongestSubstring("bbbbb") << endl;
    cout << lengthOfLongestSubstring("pwwkew") << endl;
}