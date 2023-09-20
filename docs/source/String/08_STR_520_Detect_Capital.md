# Detect Capital 

## [Problem statement](https://leetcode.com/problems/detect-capital/)

The task is to determine if the usage of capital letters in a given string, `word`, is correct according to the following rules:

1. All letters in the word are capital, like "USA".
2. All letters in the word are not capital, like "leetcode".
3. Only the first letter in the word is capital, like "Google".

If the capitalization in the given word adheres to these rules, the function should return `true`; otherwise, it should return `false`. 

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

### Code explanation

1. The function **`isValidCase`** is used to check whether a given character `c` is a valid uppercase or lowercase letter based on the value of the `isLower` parameter.

2. The function **`detectCapitalUse`** begins by checking if the length of the input string `word` is 1. If the word has only one character, it is considered valid (as it doesn't violate any capitalization rule), and the function returns `true`.

3. The `isLower` variable is initialized to `true`, assuming that all letters in `word` are initially lowercase.

4. The code then examines the first two characters of the word (if they exist). If both characters are uppercase, it sets `isLower` to `false` since this indicates that the word follows rule 1 (all uppercase).
   
5. The loop then iterates through the rest of the characters in the word, starting from the third character (if it exists). Within the loop, for each character at position `i`, it calls the `isValidCase` function to check if the character `word[i]` is valid for the current capitalization type (`isLower`).
   
6. If the character is found to be invalid based on the current capitalization type, the function returns `false` immediately, indicating that the word doesn't adhere to the capitalization rule. If the loop completes without finding any violations, it means that the word adheres to one of the capitalization rules, and the function returns `true`.

In summary, this solution efficiently checks whether a given word follows one of the specified capitalization rules by iterating through the characters of the word and using the `isValidCase` function to validate each character's capitalization based on the current capitalization type (`isLower`). If no violations are found, the word is considered valid, and the function returns `true`. 

### Complexity
* Runtime: `O(N)`, where `N = word.length`.
* Extra space: `O(1)`.



