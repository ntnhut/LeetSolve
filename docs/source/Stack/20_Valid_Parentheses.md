# Valid Parentheses
% Easy
## Problem statement
 
[^url]You are given a string `s` containing only the characters `'('`, `')'`, `'{'`, `'}'`, `'['`, and `']'`. Your task is to check if the input string is valid.

A string is considered valid if the following conditions are satisfied:

1. Opening brackets must be closed by the same type of brackets.
2. Opening brackets must be closed in the correct order, meaning that the innermost opening bracket should be closed before its surrounding brackets.

[^url]: https://leetcode.com/problems/valid-parentheses/

### Example 1
```text
Input: s = "()"
Output: true
```
### Example 2
```text
Input: s = "()[]{}"
Output: true
```

### Example 3
```text
Input: s = "(]"
Output: false
``` 

### Constraints

* `1 <= s.length <= 10^4`.
* `s` consists of parentheses only `'()[]{}'`.

## Solution: Using a stack
For each character `c` of `s`:

1. If it is an open parenthesis (`'('`, `'{'`, or `'['`), push it into the stack.
2. If it is a closed parenthesis (`')'`, `'}'`, or `']'`) but its previous character is not the corresponding open one, return `false`. End.
3. Otherwise (i.e. match open-closed), erase the pair.
4. Continue the process until all characters of `s` are visited.
5. Return `true` if the stack is empty, i.e. all valid pairs are erased.

### Code
```cpp
#include <iostream>
#include <stack>
using namespace std;
bool isValid(const string& s) {
    stack<char> stk;
    for (auto& c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (stk.empty()) {
            // start with a non-open parenthesis is invalid
            return false;
        } else if (c == ')' && stk.top() != '(' 
              || c == ']' && stk.top() != '['
              || c == '}' && stk.top() != '{') {
            // the last open parenthesis does not match this closed one
            return false;
        } else {
            // open-close match
            stk.pop();
        }
    }
    return stk.empty();
}
int main() {
    cout << isValid("()") << endl;
    cout << isValid("(){}[]") << endl;
    cout << isValid("(]") << endl;
    cout << isValid("([)]") << endl;
}
```
```text
Output:
1
1
0
0
```

### Complexity:

* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

## Conclusion

This solution efficiently checks the validity of a string of parentheses, brackets, and curly braces by using a stack to ensure that each opening bracket is correctly matched with its corresponding closing bracket. 

## Exercise
- Check If Word Is Valid After Substitutions[^ex].

[^ex]: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/