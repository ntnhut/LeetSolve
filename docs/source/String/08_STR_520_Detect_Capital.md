# Detect Capital 

## [Problem statement](https://leetcode.com/problems/detect-capital/)
We define the usage of capitals in a word to be right when one of the following cases holds:

- All letters in this word are capitals, like `"USA"`.
- All letters in this word are not capitals, like `"leetcode"`.
- Only the first letter in this word is capital, like `"Google"`.

Given a string `word`, return `true` if the usage of capitals in it is right.

 

### Example 1
```text
Input: word = "USA"
Output: true
```

### Example 2
```text
Input: word = "FlaG"
Output: false
```
 

### Constraints

* `1 <= word.length <= 100`,
* `word` consists of lowercase and uppercase English letters.

## Solution 
Only when the first two characters of the `word` are uppercase, the rest must be the same.
Otherwise, the rest is always lowercase.


### Code
```cpp
#include <string>
#include <iostream>
using namespace std;
bool isValidCase(const char& c, const bool isLower) {
    if (isLower) {
        return 'a' <= c && c <= 'z';
    }
    return 'A' <= c && c <= 'Z';
}
bool detectCapitalUse(string word) {
    if (word.length() == 1) {
        return true;
    }
    bool isLower = true;
    if (isValidCase(word[0], false) && isValidCase(word[1], false)) {
        isLower = false;
    }
    for (int i = 1; i < word.length(); i++) {
        if (!isValidCase(word[i], isLower)) {
            return false;
        }
    }
    return true;
}
int main() {
    cout << detectCapitalUse("USA") << endl;
    cout << detectCapitalUse("FlaG") << endl;
    cout << detectCapitalUse("leetcode") << endl;
    cout << detectCapitalUse("Google") << endl;
}
```
```text
Output:
1
0
1
1
```

### Complexity
* Runtime: `O(N)`, where `N = word.length`.
* Extra space: `O(1)`.



