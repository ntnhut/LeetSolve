# Valid Parentheses

## [Problem statement](https://leetcode.com/problems/valid-parentheses/)
 
You are given a string `s` containing only the characters `'('`, `')'`, `'{'`, `'}'`, `'['`, and `']'`. Your task is to check if the input string is valid.

A string is considered valid if the following conditions are satisfied:

1. Opening brackets must be closed by the same type of brackets.
2. Opening brackets must be closed in the correct order, meaning that the innermost opening bracket should be closed before its surrounding brackets.

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

## Solution: Using a {index}`stack`
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
        } else if (c == ')' && stk.top() != '(' 
              || c == ']' && stk.top() != '['
              || c == '}' && stk.top() != '{') {
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
```text
Output:
1
1
0
0
```

### Code explanation

1. The code uses a stack data structure, represented by `stack<char> stk`, to keep track of the opening brackets as they are encountered.

2. The code iterates through each character in the input string `s`.

   - If the current character `c` is an opening bracket (`'('`, `'['`, or `'{'`), the code pushes it onto the stack `stk`. This indicates that an opening bracket has been encountered and needs to be matched later with a closing bracket.

   - If the current character `c` is a closing bracket (`')'`, `']'`, or `'}'`), the code checks the stack for a matching opening bracket.
   - If the stack is empty, meaning there is no corresponding opening bracket, the code immediately returns `false`, as this is an invalid sequence.
   - If the stack is not empty, the code compares the current closing bracket with the top element of the stack (`stk.top()`) to check if they match. If they match, the opening bracket is popped from the stack because it has been successfully matched with a closing bracket.
   - If the current closing bracket does not match the top element of the stack, the code returns `false` because the sequence is invalid.

3. After processing all characters in the input string, the code checks if the stack is empty. If the stack is empty, it means that all opening brackets have been successfully matched with closing brackets, and the input string is considered valid. If the stack is not empty, there are unmatched opening brackets remaining, and the input string is considered invalid.


### Complexity:
This solution efficiently checks the validity of a string of parentheses, brackets, and curly braces by using a stack to ensure that each opening bracket is correctly matched with its corresponding closing bracket. 

* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

