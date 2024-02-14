# Remove All Adjacent Duplicates in String II
% Medium https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
## Problem statement

You are given a string `s` and an integer `k`. A `k` duplicate removal operation involves selecting `k` adjacent and identical letters from `s` and removing them, causing the remaining portions on the left and right of the removed substring to join together.

You need to perform the `k` duplicate removal operation on `s` repeatedly until it is no longer possible. After completing all such operations, return the resulting string. It is guaranteed that the answer will be unique.

### Example 1
```text
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There is nothing to delete.
```

### Example 2
```text
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
```

### Example 3
```text
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
``` 

### Constraints

* `1 <= s.length <= 10^5`.
* `2 <= k <= 10^4`.
* `s` only contains lower case English letters.

## Solution: Strings of adjacent equal letters 

Construct a stack of strings that has adjacent equal letters and perform the removal during building those strings.

### Example 2
For `s = "deeedbbcccbdaa"` and `k = 3`:

* The first built string is `"d"`.
* Then `"eee"` with the exact length `k`, remove this string.
* The next character is `'d'`, which equals the last character of the last string `"d"`, merge them together. The first string becomes `"dd"`.
* The next string is `"bb"`.
* Then `"ccc"` is removed.
* The next character `'b'` is merged with the last string (`"bb"`) to become `"bbb"` and be removed.
* The next character `'d'` is merged with the last string (`"dd"`) to become `"ddd"` and be removed.
* The remaining string is `"aa"`.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
string removeDuplicates(string s, int k) {
    vector<string> stk;
    int i = 0;
    while (i < s.length()) {
        string a;   // to store adjacent equal letters        
        // perform the merge
        if (!stk.empty() && s[i] == stk.back().back()) {
            a = move(stk.back());
            stk.pop_back();
        }
        int j = i;
        while (j < s.length() && s[j] == s[i]) {
            a += s[j];
            // remove the k-duplicate
            if (a.length() == k) {
                a = "";
            }
            j++;
        }
        if (!a.empty()) {
            stk.push_back(a);
        }
        i = j;
    }
    s = "";
    for (auto& str : stk) {
        s += str;
    }
    return s;
}
int main() {
    cout << removeDuplicates("abcd", 2) << endl;
    cout << removeDuplicates("deeedbbcccbdaa", 3) << endl;
    cout << removeDuplicates("pbbcggttciiippooaais", 2) << endl;
}
```
```text
Output:
abcd
aa
ps
```

This solution efficiently removes substrings of consecutive duplicate characters of length `k` from a given string by using a stack to keep track of the adjacent characters. 

### Complexity

* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

```{admonition} Implementation tips
:class: tip

The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use [`std::vector`](https://en.cppreference.com/w/cpp/container/vector):

* `std::vector` also has methods [`push_back(value)`](https://en.cppreference.com/w/cpp/container/vector/push_back) and [`pop_back()`](https://en.cppreference.com/w/cpp/container/vector/pop_back) like the ones in a stack.
* On the other hand, it is faster for a vector to perform the string concatenation at the end.

```

## Exercise
- [Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)