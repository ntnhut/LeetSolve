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

### Code explanation

1. The code begins by comparing the lengths of the two strings. If the lengths are different, it immediately returns `false` because two strings with different lengths cannot be anagrams.

2. If the lengths are the same, the code proceeds to sort both strings in lexicographical order. This step is crucial for comparing anagrams because it rearranges the characters in both strings such that if they are anagrams, they will now be identical.

3. After sorting both strings, the code compares them using the equality operator (`==`). If the sorted `s` and `t` are equal, it means that the original `s` and `t` are anagrams, and the function returns `true`. Otherwise, it returns `false`.

In summary, this code determines if two strings are anagrams by comparing their sorted versions. If the sorted versions are equal, the original strings are anagrams, and the function returns `true`. Otherwise, it returns `false`. 

### Complexity
* Runtime: `O(NlogN)`, where `N = s.length`.
* Extra space: `O(1)`.


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

### Code explanation

1. If the lengths of the two strings are the same, the code proceeds to check the characters and their frequencies in both strings using an array called `alphabet`. This array is used to store the frequency of each character in the English alphabet. It is initialized with all values set to zero.

2. The code then iterates through the characters of string `s` to count the frequency for the character `c` in the `alphabet` array. Here you map `0 -> 'a'`, `1 -> 'b'`, ..., `25 -> 'z'`.

3. Next, the code iterates through the characters of string `t` and decrements the count for the character `c` in the `alphabet` array and checks if it becomes negative. If it becomes negative, it means that `t` has more occurrences of the character `c` than `s`, so the function returns `false`.

4. If the code successfully completes the loops without returning `false`, it means that `s` and `t` are anagrams of each other, and the function returns `true`.

In summary, this code efficiently determines if two strings are anagrams by counting the frequency of each character in both strings using an array. If the character frequencies match for both strings, they are anagrams, and the function returns `true`. Otherwise, it returns `false`. 

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

### Code explanation

Instead of relying on a fixed-size array like the ASCII-based solutions, this solution uses an `unordered_map` to store character frequencies. Each character is used as a key in the map, and the count of occurrences is stored as the associated value.

Unicode characters can have variable lengths in terms of bytes or code points, and their values are not restricted to a specific range. The `unordered_map` approach accommodates this variability by allowing any character to be a key.

In summary, this solution is Unicode-friendly because it relies on the flexible `unordered_map` data structure to count character frequencies and doesn't make any assumptions about the character encoding or specific character ranges. It's a general and robust approach that can handle a wide range of character sets, including Unicode.

### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(c)` where `c` represents the number of unique characters present in both strings `s` and `t`.




