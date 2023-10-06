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

### Code explanation

1. The code initializes an unordered map `count` where characters from the string are keys, and their corresponding counts (how many times they appear in the string) are values.

2. The loop then iterates through the characters of the string `s`. For each character `c` encountered, it increments its count in the `count` map.

3. After counting all the characters in the string, it performs a second loop, this time using an index variable `i` that starts from 0 and goes up to the length of the string `s`.

4. In this loop, it checks whether the count of the character at the current index `i` is equal to 1. If it is, this means that the character is unique in the string, and the function returns `i`, which is the index of the first occurrence of that unique character.

5. If no unique character is found during the loop, the function returns -1 to indicate that there are no unique characters in the string.


### Complexity
This solution has a time complexity of `O(n)`, where `n` is the length of the string `s`, because it iterates through the string twice: once to count the characters and once to find the first unique character. 

It also has a space complexity of `O(k)`, where `k` is the number of distinct characters in the string, as it stores character counts in the `count` unordered map. As the problem considers only lowercase English letters, `k = 26`, you can give it `O(1)` complexity.

* Runtime: `O(n)`.
* Extra space: `O(1)`.

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
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(1)`.


