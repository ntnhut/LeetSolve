# First Unique Character in a String

## [Problem statement](https://leetcode.com/problems/first-unique-character-in-a-string/)

You have a string called `s`. Your objective is to locate the index of the first character in the string that does not repeat anywhere else in the string. If such a character doesn't exist, return `-1`.

### Example 1
```text
Input: s = "leetcode"
Output: 0
```

### Example 2
```text
Input: s = "loveleetcode"
Output: 2
```

### Example 3
```text
Input: s = "aabb"
Output: -1
``` 

### Constraints

* `1 <= s.length <= 10^5`.
* `s` consists of only lowercase English letters.

## Solution 1: Using a map to store the appearances

### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
int firstUniqChar(string s) {
    unordered_map<char, int> count;
    for (char& c : s) {
        count[c]++;
    }
    for (int i = 0; i < s.length(); i++) {
        if (count[s[i]] == 1) {
            return i;
        }
    }
    return -1;
}
int main() {
    cout << firstUniqChar("leetcode") << endl;
    cout << firstUniqChar("loveleetcode") << endl;
    cout << firstUniqChar("aabb") << endl;
}
```
```text
Output:
0
2
-1
```

This solution efficiently finds the index of the first non-repeating character in a string by using an unordered map to count the occurrences of each character. 

By iterating through the string and populating the unordered map with the count of each character, it efficiently constructs the character count. Then, it iterates through the string again and returns the index of the first character with a count of 1, indicating that it is non-repeating. 

This approach optimizes the computation by efficiently tracking the count of each character and identifying the first non-repeating character without requiring additional space proportional to the length of the string.

### Complexity

* Runtime: `O(n)`, where `n` is the length of the string `s`.
* Extra space: `O(1)` as the problem considers only 26 lowercase English letters.

## Solution 2: Using an array to store the appearances

From the constraints "`s` consists of only lowercase English letters", you can use an array of 26 elements to store the counts.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int firstUniqChar(string s) {
    // initializes an array of 26 elements, all set to zero
    std::array<int, 26> count{};
    for (char& c : s) {
        count[c - 'a']++;
    }
    for (int i = 0; i < s.length(); i++) {
        if (count[s[i] - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}
int main() {
    cout << firstUniqChar("leetcode") << endl;
    cout << firstUniqChar("loveleetcode") << endl;
    cout << firstUniqChar("aabb") << endl;
}
```
```text
Output:
0
2
-1
```

### Complexity
* Runtime: `O(n)`, where `n = s.length`.
* Extra space: `O(1)` as the array is fixed regardless of how big `n` is.
