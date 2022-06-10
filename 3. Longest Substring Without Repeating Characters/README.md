# 3. Longest Substring Without Repeating Characters
Tag: string

## Problem statement

Given a string `s`, find the length of the longest substring without repeating characters.

### Example 1
```plain
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

### Example 2
```plain
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

### Example 3
```plain
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
``` 

### Constraints

* `0 <= s.length <= 5 * 10^4`.
* `s` consists of English letters, digits, symbols and spaces.

## Solution: Store the position of the visited characters

### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> position;
    int maxLen = 0;
    int start = 0;
    for (int i = 0; i < s.length(); i++) {
        if (position.find(s[i]) != position.end()) {
            start = max(start, position[s[i]] + 1);
        }
        position[s[i]] = i;
        maxLen = max(maxLen, i - start + 1);
    }
    return maxLen;
}
int main() {
    cout << lengthOfLongestSubstring("abcabcbb") << endl;
    cout << lengthOfLongestSubstring("bbbbb") << endl;
    cout << lengthOfLongestSubstring("pwwkew") << endl;
}
```
```plain
Output:
3
1
3
```

### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

## References
* [https://leetcode.com/problems/longest-substring-without-repeating-characters/](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
* [https://www.leetsolve.com/3-longest-substring-without-repeating-characters](https://www.leetsolve.com/3-longest-substring-without-repeating-characters)