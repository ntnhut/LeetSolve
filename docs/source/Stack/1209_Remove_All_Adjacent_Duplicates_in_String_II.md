# Remove All Adjacent Duplicates in String II
% Medium
## Problem statement

[^url]You are given a string `s` and an integer `k`. A `k` duplicate removal operation involves selecting `k` adjacent and identical letters from `s` and removing them, causing the remaining portions on the left and right of the removed substring to join together.

You need to perform the `k` duplicate removal operation on `s` repeatedly until it is no longer possible. After completing all such operations, return the resulting string. It is guaranteed that the answer will be unique.

[^url]: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
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
string removeDuplicates(string& s, int k) {
    // stk is used as a stack
    // all letters in each string a of stk are equal 
    // every a's length is less than k
    vector<string> stk;
    int i = 0;
    while (i < s.length()) {
        // a represents the current string with duplicate letters
        string a;   
        
        if (!stk.empty() && s[i] == stk.back().back()) {
            // let a be the latest string in stk
            // because its letters are equal to s[i]
            a = move(stk.back());
            stk.pop_back();
        }
        int j = i;
        // iterate all adjacent duplicates of s[i]
        while (j < s.length() && s[j] == s[i]) {
            a += s[j];
            // remove the k-duplicate
            if (a.length() == k) {
                a = "";
            }
            j++;
        }
        // after the loop, the number of duplicates in a is less than k
        if (!a.empty()) {            
            stk.push_back(a);
        }
        i = j;
    }
    // create the final result from stk
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

## Implementation tips

* The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use `std::vector`:

* `std::vector` also has methods `push_back(value)` and `pop_back()` like the ones in a stack.

* On the other hand, it is faster for a vector to perform the string concatenation at the end.

* In the expression `stk.back().back()`: `stk.back()` is the latest string `a` of `stk`. Then `stk.back().back() = a.back()` is the last character of `a`.

## Exercise
- Remove All Adjacent Duplicates In String[^ex].

[^ex]: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/