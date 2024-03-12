# Valid Anagram
% Easy
## Problem statement

[^url]You are given two strings, `s` and `t`. Your task is to determine whether `t` is an anagram of `s`. If `t` is an anagram of `s`, return `true`; otherwise, return `false`.

An **anagram** is a term that describes a word or phrase formed by rearranging the letters of another word or phrase, typically using all the original letters exactly once. 

[^url]: https://leetcode.com/problems/valid-anagram/
### Example 1
```text
Input: s = "anagram", t = "nagaram"
Output: true
```

### Example 2
```text
Input: s = "rat", t = "car"
Output: false
``` 

### Constraints

* `1 <= s.length, t.length <= 5 * 10^4`.
* `s` and `t` consist of lowercase English letters.
 

### Follow up
* What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

## Solution 1: Rearrange both `s` and `t` into a sorted string

### Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
bool isAnagram(string& s, string& t) {
    // anagrams must have the same length
    if (s.length() != t.length()) {
        return false;
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}
int main() {
    cout << isAnagram("anagram", "nagaram") << endl;
    cout << isAnagram("rat", "car") << endl;
}
```
```text
Output:
1
0
```

This solution determines if two strings are anagrams by comparing their sorted versions. If the sorted versions are equal, the original strings are anagrams, and the function returns `true`. Otherwise, it returns `false`. 

### Complexity
* Runtime: `O(NlogN)`, where `N = s.length`.
* Extra space: `O(1)`.


## Solution 2: Count the appearances of each letter

### Code
```cpp
#include <iostream>
using namespace std;
bool isAnagram(const string& s, const string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    // s and t consist of only lowercase English letters
    // you can encode 0: 'a', 1: 'b', .., 25: 'z'.
    int alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 0;
    }
    // count the frequency of each letter in s
    for (auto& c : s) {
        alphabet[c - 'a']++;
    }
    for (auto& c : t) {
        alphabet[c - 'a']--;
        // if s and t have the same length but are not anagrams,
        // there must be some letter in t having higher frequency than s 
        if (alphabet[c - 'a'] < 0) {
            return false;
        }
    }
    return true;    
}
int main() {
    cout << isAnagram("anagram", "nagaram") << endl;
    cout << isAnagram("rat", "car") << endl;
}
```
```text
Output:
1
0
```

This solution efficiently determines if two strings are anagrams by counting the frequency of each character in both strings using an array. If the character frequencies match for both strings, they are anagrams. 

### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(1)`.

## Solution 3: If the inputs contain Unicode characters

Replace the array `alphabet` in Solution 2 with a map.

### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
bool isAnagram(const string& s, const string& t) {
    if (s.length() != t.length()) {
        return false;
    }
    // this alphabet can store all UTF-8 characters
    unordered_map<char, int> alphabet;
    for (auto& c : s) {
        alphabet[c]++;
    }
    for (auto& c : t) {
        alphabet[c]--;
        if (alphabet[c] < 0) {
            return false;
        }
    }
    return true;    
}
int main() {
    cout << isAnagram("anagram", "nagaram") << endl;
    cout << isAnagram("rat", "car") << endl;
}
```
```text
Output:
1
0
```

### Complexity

* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(c)` where `c` represents the number of unique characters present in both strings `s` and `t`.

## Key Takeaway

Instead of relying on a fixed-size array like the ASCII-based solutions, Solution 3 uses an `unordered_map` to store character frequencies. Each character is used as a key in the map, and the count of occurrences is stored as the associated value.

Unicode characters values are not restricted to a specific range. The `unordered_map` approach accommodates this variability by allowing any character to be a key.

## Exercise
- Find Resultant Array After Removing Anagrams[^ex].

[^ex]: https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/