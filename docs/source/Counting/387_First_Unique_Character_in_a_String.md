# First Unique Character in a String

## [Problem statement](https://leetcode.com/problems/first-unique-character-in-a-string/)

Given a string `s`, find the first non-repeating character in it and return its index. If it does not exist, return `-1`.

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

## Solution 1: Using map to store the appearances

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

### Complexity
* Runtime: $O(N)$, where $N$ is `s.length`.
* Extra space: $O(26)$.

## Solution 2: Using vector to store the appearances

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int firstUniqChar(string s) {
    vector<int> count(26);
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
* Runtime: $O(N)$, where $N$ is `s.length`.
* Extra space: $O(26)$.


