# Backspace String Compare
% Easy https://leetcode.com/problems/backspace-string-compare/
## Problem statement

You are provided with two strings, `s` and `t`. Your task is to determine if these two strings are equal when typed into an empty text editor, where the character `'#'` represents a backspace action.

Note that applying a backspace action to an empty text does not change the text; it remains empty. Your function should return `true` if the two strings become equal after considering the backspace actions, otherwise return `false`. 

### Example 1
```text
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
```

### Example 2
```text
Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".
```

### Example 3
```text
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".
``` 

### Constraints

* `1 <= s.length, t.length <= 200`.
* `s` and `t` only contain lowercase letters and `'#'` characters.
 

**Follow up**: Can you solve it in `O(n)` time and `O(1)` space?

## Solution: Build and clean the string using the `stack`'s behaviors

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
string cleanString(string &s) {
    vector<char> v;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '#') {
            v.push_back(s[i]);
        } else {
            if (!v.empty()) {
                v.pop_back();
            }
        }
    }
    return string(v.begin(), v.end());
}
bool backspaceCompare(string s, string t) {
    return cleanString(s) == cleanString(t);
}
int main() {
    cout << backspaceCompare("ab#c", "ad#c") << endl;
    cout << backspaceCompare("ab##", "c#d#") << endl;
    cout << backspaceCompare("a#c", "b") << endl;
}
```
```text
Output:
1
1
0
```

This solution effectively handles backspace characters (`'#'`) in input strings `s` and `t` by constructing cleaned versions of the strings and then comparing the cleaned strings for equality.

### Complexity

* Runtime: `O(n)`, where `n = max(s.length, t.length)`.
* Extra space: `O(n)`. 

```{admonition} Implementation notes
:class: tip

**Why `vector ` instead of `stack`?**

You can use the methods [`push`](https://en.cppreference.com/w/cpp/container/stack/push) and [`pop`](https://en.cppreference.com/w/cpp/container/stack/pop) of the data structure [`stack`](https://en.cppreference.com/w/cpp/container/stack) to build and clean the strings. 

But [`vector`](https://en.cppreference.com/w/cpp/container/vector) has also such methods: [`push_back`](https://en.cppreference.com/w/cpp/container/vector/push_back) and [`pop_back`](https://en.cppreference.com/w/cpp/container/vector/pop_back).

On the other hand, using `vector` it is easier to construct a `string` by constructor than using `stack` after cleaning.

**Can you solve it in `O(n)` time and `O(1)` space?**

Yes, you can. 

The simplest way is just to perform the erasure directly on strings `s` and `t`. But the run time complexity of [`string::erase`](https://en.cppreference.com/w/cpp/string/basic_string/erase)  is not constant.

```

## Exercise
- [Removing Stars From a String](https://leetcode.com/problems/removing-stars-from-a-string/)