## 3. Longest Substring Without Repeating Characters
Tag: string

### Problem statement

Given a string `s`, find the length of the longest substring without repeating characters.

#### Example 1
```plain
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.
```

#### Example 2
```plain
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

#### Example 3
```plain
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with a length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
``` 

#### Constraints

* `0 <= s.length <= 5 * 10^4`.
* `s` consists of English letters, digits, symbols and spaces.

### Solution: Store the position of the visited characters

Whenever you meet a visited character `s[i] == s[j]` for some `0 <= i < j < s.length`, the substring `"s[i]...s[j - 1]"` might be valid, i.e. it consist of only nonrepeating characters.

But in case you meet another visited character `s[x] == s[y]` where `x < i < j < y`, the substring `"s[x]...s[y - 1]"` is not valid because it consists of repeated character `s[i] == s[j]`. 

That shows the substring `"s[i]...s[j - 1]"` is not always a valid one. You might need to find the right starting position `start >= i` for the valid substring `"s[start]...s[j - 1]"`.

#### Example 4 
For the string `s = "babba"`:

* When you visit the second letter `'b'`, the substring `"ba"` is a valid one. 
* When you visit the third letter `'b'`, the substring of interest should be started by the second letter `'b'`. It gives you the substring `"b"`.
* When you visit the second letter `'a'`, the substring `"abb"` is not a valid one since `'b'` is repeated. To ensure no repetition, the starting position for this substring should be the latter `'b'`, which leads to the valid substring `"b"`.
* The final longest valid substring is `"ba"` with length 2.

Example 4 shows the starting position `start` for the substring of interest `"s[i]...s[j - 1]"` should be:

```plain
this_start = max(previous_start, i).
```

#### Code
```cpp
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
```
```plain
Output:
3
1
3
```

#### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

### References
* [https://leetcode.com/problems/longest-substring-without-repeating-characters/](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
* [https://www.leetsolve.com/3-longest-substring-without-repeating-characters](https://www.leetsolve.com/3-longest-substring-without-repeating-characters)