# 20. Valid Parentheses

## Problem statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
 

### Example 1
```plain
Input: s = "()"
Output: true
```
### Example 2
```plain
Input: s = "()[]{}"
Output: true
```

### Example 3
```plain
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
bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (stk.empty()) {
            return false;
        } else if  (c == ')' && stk.top() != '(' ||
                    c == ']' && stk.top() != '[' ||
                    c == '}' && stk.top() != '{') {
            return false;
        } else {
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
```plain
Output:
1
1
0
0
```

### Complexity:
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N/2)`.

## References
* [https://leetcode.com/problems/valid-parentheses/](https://leetcode.com/problems/valid-parentheses/)
* [https://www.leetsolve.com/20-valid-parentheses](https://www.leetsolve.com/20-valid-parentheses)