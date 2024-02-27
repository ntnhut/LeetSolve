# Detect Capital 
% Easy
## Problem statement

[^url]The task is to determine if the usage of capital letters in a given string, `word`, is correct according to the following rules:

1. All letters in the word are capital, like "USA".
2. All letters in the word are not capital, like "leetcode".
3. Only the first letter in the word is capital, like "Google".

If the capitalization in the given word adheres to these rules, the function should return `true`; otherwise, it should return `false`. 

[^url]: https://leetcode.com/problems/detect-capital/
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
//! @return true if (c is lowercase and isLower is true) 
//!                 or (c is uppercase and isLower is false).
//!         false, otherwise. 
bool isValidCase(const char& c, const bool isLower) {
    if (isLower) {
        return 'a' <= c && c <= 'z';
    }
    return 'A' <= c && c <= 'Z';
}
bool detectCapitalUse(const string& word) {
    if (word.length() == 1) {
        return true;
    }
    bool isLower = true;
    
    // if the first two characters are uppercase,
    // the rest must be uppercase, too.
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

## Conclusion

This solution efficiently checks whether a given word follows one of the specified capitalization rules by iterating through the characters of the word and using the `isValidCase` function to validate each character's capitalization based on the current capitalization type (`isLower`). If no violations are found, the word is considered valid, and the function returns `true`. 

## Exercise
- [Capitalize the Title](https://leetcode.com/problems/capitalize-the-title/)

