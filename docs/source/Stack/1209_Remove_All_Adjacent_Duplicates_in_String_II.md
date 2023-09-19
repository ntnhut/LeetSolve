# Remove All Adjacent Duplicates in String II

## [Problem statement](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/)

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
```

### Code explanation

1. The code uses a `vector<string>` called `stk` to simulate a stack, where each element represents a substring of consecutive duplicate characters.

2. Within the outer loop, the code starts by defining an empty string `a` to store adjacent equal letters, which will form a substring of consecutive duplicates.

   - If the stack is not empty and the current character `s[i]` is the same as the last character of the top string in the stack (`stk.back().back()`), it means that the current character belongs to the same group of consecutive duplicates as the top string in the stack. In this case, the code performs a merge by moving the top string from the stack to `a` and then removing it from the stack.
   
3. The code enters another `while` loop that iterates as long as the characters are the same as `s[i]`. During this loop, the code appends the current character `s[j]` to the `a` string.

   - While building the substring, if the length of `a` becomes equal to `k`, it means that `a` represents a substring of length `k` that consists of consecutive duplicate characters. In this case, the code sets `a` to an empty string to remove the `k`-duplicate.
   - The loop continues to process consecutive characters until a different character is encountered.

4. If the `a` string is not empty after processing, it means that it represents a substring of consecutive characters that may be shorter than `k` (if `k` consecutive duplicates were not found). The code pushes this substring onto the stack `stk`.

5. After processing a group of consecutive duplicate characters, the index `i` is updated to the value of `j`, which points to the next character in the string that needs to be processed.

6. After processing the entire input string `s`, the code constructs the result string `s` by iterating through the `stk` vector and appending each string in the vector to the result.

7. The code returns the final result string `s`, which contains the input string with `k` consecutive duplicates removed.

In summary, this code efficiently removes substrings of consecutive duplicate characters of length `k` from a given string by using a stack to keep track of the adjacent characters. 

### Complexity
* Runtime: `O(N)`, where `N = s.length`.
* Extra space: `O(N)`.

```{admonition} Implementation tips
:class: tip

The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use [`std::vector`](https://en.cppreference.com/w/cpp/container/vector):

* `std::vector` also has methods [`push_back(value)`](https://en.cppreference.com/w/cpp/container/vector/push_back) and [`pop_back()`](https://en.cppreference.com/w/cpp/container/vector/pop_back) like the ones in a stack.
* On the other hand, it is faster for a vector to perform the string concatenation at the end.

```