# Longest Substring Without Repeating Characters

## [Problem statement](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

Given a string `s`, your task is to determine the length of the longest substring within `s` that does not contain any repeating characters.

### Example 1
```text
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with a length of 3.
```

### Example 2
```text
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

### Example 3
```text
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with a length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
``` 

### Constraints

* `0 <= s.length <= 5 * 10^4`.
* `s` consists of English letters, digits, symbols and spaces.

## Solution: Store the position of the visited characters

Whenever you meet a visited character `s[i] == s[j]` for some `0 <= i < j < s.length`, the substring `"s[i]...s[j - 1]"` might be valid, i.e. it consist of only nonrepeating characters.

But in case you meet another visited character `s[x] == s[y]` where `x < i < j < y`, the substring `"s[x]...s[y - 1]"` is not valid because it consists of repeated character `s[i] == s[j]`. 

That shows the substring `"s[i]...s[j - 1]"` is not always a valid one. You might need to find the right starting position `start >= i` for the valid substring `"s[start]...s[j - 1]"`.

### Example 4 
For the string `s = "babba"`:

* When you visit the second letter `'b'`, the substring `"ba"` is a valid one. 
* When you visit the third letter `'b'`, the substring of interest should be started by the second letter `'b'`. It gives you the substring `"b"`.
* When you visit the second letter `'a'`, the substring `"abb"` is not a valid one since `'b'` is repeated. To ensure no repetition, the starting position for this substring should be the latter `'b'`, which leads to the valid substring `"b"`.
* The final longest valid substring is `"ba"` with length 2.

Example 4 shows the starting position `start` for the substring of interest `"s[i]...s[j - 1]"` should be:

```text
this_start = max(previous_start, i).
```

### Code
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
```text
Output:
3
1
3
```

### Code explanation

1. **Initialization**:
   - An unordered map `position` is used to store the most recent position (index) where each character in the string `s` was seen.
   - `maxLen` is initialized to 0, representing the maximum substring length found so far.
   - `start` is initialized to -1. This variable will be used to keep track of the starting index of the current substring.

2. The code iterates through each character of the input string `s`. Inside the loop, the code checks whether the current character `s[i]` is already present in the `position` map. If the character is found in the map, it means that the character has occurred previously in the current substring.

3. If the character is found in the map (indicating a repeating character), the code updates the `start` index to the maximum of its current value (`start`) and the position of the character in the map (`position[s[i]]`). This step effectively "slides" the window to the right, excluding the repeating character and any characters before it.

4. The code updates the `position` map with the current character's position by setting `position[s[i]] = i`. This keeps track of the most recent position of each character.

5. At each iteration, the code calculates the length of the current substring (`i - start`) and updates `maxLen` to be the maximum of its current value and the calculated length. This ensures that `maxLen` always stores the maximum length encountered during the traversal.

5. After the loop completes, `maxLen` contains the length of the longest substring without repeating characters in the input string `s`. It is then returned as the result.


### Complexity
This solution efficiently finds the length of the longest substring without repeating characters by using a sliding window approach and an unordered map to track character positions. It iterates through the string, updates the window, and calculates the maximum length as it goes. 

* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.



