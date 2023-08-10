# Valid Anagram

## [Problem statement](https://leetcode.com/problems/valid-anagram/)

You are given two strings, `s` and `t`. Your task is to determine whether `t` is an anagram of `s`. If `t` is an anagram of `s`, return `true`; otherwise, return `false`.

An **anagram** is a term that describes a word or phrase formed by rearranging the letters of another word or phrase, typically using all the original letters exactly once. 

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
 

**Follow up**: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

## Solution 1: Rearrange both `s` and `t` into a sorted string

### Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
bool isAnagram(string s, string t) {
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

### Complexity
* Runtime: $O(N\log N)$, where $N$ is `s.length`.
* Extra space: $O(1)$.


## Solution 2: Count the appearances of each letter

### Code
```cpp
#include <iostream>
using namespace std;
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    int alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 0;
    }
    for (char& c : s) {
        alphabet[c - 'a']++;
    }
    for (char& c : t) {
        alphabet[c - 'a']--;
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

### Complexity
* Runtime: $O(N)$, where $N$ is `s.length`.
* Extra space: $O(1)$.

## Solution 3: If the inputs contain Unicode characters

Replace the array `alphabet` in Solution 2 with a map.

### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    unordered_map<char, int> alphabet;
    for (char& c : s) {
        alphabet[c]++;
    }
    for (char& c : t) {
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
* Runtime: $O(N)$, where $N$ is `s.length`.
* Extra space: $O(1)$.




