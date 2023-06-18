# 3. Longest Substring Without Repeating Characters

## [Problem statement](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

Given a string `s`, find the length of the longest substring without repeating characters.

### Example 1

```plaintext
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.
```

### Example 2

```plaintext
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

### Example 3

```plaintext
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with a length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

### Constraints

* `0 <= s.length <= 5 * 10^4`.
    
* `s` consists of English letters, digits, symbols and spaces.
    

## Solution: Store the position of the visited characters

One way of checking the repetition of the characters is by using a map to store their indices. For example:

```plaintext
last_visit[s[i]] = i
```

You might want to find every substring of nonrepeating characters in the string `s`, then identify the longest one among them.

1. The character you are checking its repetition and computing the length should be done within its substring;
    
2. The map should always update the latest visited index of a character; and
    
3. The starting index of a substring is also updated when repetition happens.
    

### Example 1

For the string `s = "abcabcbb"`:

* When you visit the second letter `'a'`, the first substring is formed `"abc"`, the next substring starts from the second letter `'a'`: `start = 3` , `last_visit['a']` is updated to be `3`.
    
* When you visit the second letter `'b'`, its `last_visit['b']` is updated to be `4`.
    
* Repetition is found when you visit the third letter `'b'`, the second substring `"abc"` is formed. The next `start = 6`; `last_visit['b'] = 6`.
    
* The fourth letter `'b'` causes a repetition and forms a one-letter substring `"b"`.
    
* The string `s` ends and form another one-letter substring `"b"`.
    

### Code

```cpp
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> last_visit;
    int maxLen = 0;
    int start = -1;
    for (int i = 0; i < s.length(); i++) {
        auto it = last_visit.find(s.at(i));
        if (it != last_visit.end()) {
            start = max(start, it->second);
            it->second = i;
        } else {
            last_visit.insert({s.at(i), i});
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
```

```plaintext
Output:
3
1
3
```

### Complexity

* Runtime: `O(N)`, where `N = s.length`.
    
* Extra space: `O(N)`.
    

## Implementation notes

* You can initialize the `start` index of the substrings with `-1` to deal with the boundary cases.
    
* As a best practice, when you check if a map contains a key and retrieve its value, use an iterator and `find()` like the above solution. DO NOT implement as follow
    

```cpp
if (last_visit.find(s.at(i)) != last_visit.end()) {
    start = max(start, last_visit[s.at(i)]);
}
```

Because the operator `[]` might perform an additional `find()`.
