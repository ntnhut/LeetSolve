## 1209. Remove All Adjacent Duplicates in String II
Tag: string, stack

### Problem statement

You are given a string `s` and an integer `k`, a `k` duplicate removal consists of choosing `k` adjacent and the same letters from `s` and removing them, causing the left and the right side of the deleted substring to concatenate together.

We repeatedly make `k` duplicate removals on `s` until we no longer can.

Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.

#### Example 1
```plain
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There is nothing to delete.
```

#### Example 2
```plain
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation: 
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
```

#### Example 3
```plain
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
``` 

#### Constraints

* `1 <= s.length <= 10^5`.
* `2 <= k <= 10^4`.
* `s` only contains lower case English letters.

### Solution: Strings of adjacent equal letters 

Construct a stack of strings that has adjacent equal letters and perform the removal during building those strings.

#### Example 2
For `s = "deeedbbcccbdaa"` and `k = 3`:

* The first built string is `"d"`.
* Then `"eee"` with the exact length `k`, remove this string.
* The next character is `'d'`, which equals the last character of the last string `"d"`, merge them together. The first string becomes `"dd"`.
* The next string is `"bb"`.
* Then `"ccc"` is removed.
* The next character `'b'` is merged with the last string (`"bb"`) to become `"bbb"` and be removed.
* The next character `'d'` is merged with the last string (`"dd"`) to become `"ddd"` and be removed.
* The remaining string is `"aa"`.

#### Code
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
```plain
Output:
abcd
aa
ps
```

#### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

### Implementation notes
The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use [`std::vector`](https://en.cppreference.com/w/cpp/container/vector):

* `std::vector` also has methods [`push_back(value)`](https://en.cppreference.com/w/cpp/container/vector/push_back) and [`pop_back()`](https://en.cppreference.com/w/cpp/container/vector/pop_back) like the ones in a stack.
* On the other hand, it is faster for a vector to perform the string concatenation at the end.

### References
* [https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/)
* [https://www.leetsolve.com/1209-remove-all-adjacent-duplicates-in-string-ii](https://www.leetsolve.com/1209-remove-all-adjacent-duplicates-in-string-ii)