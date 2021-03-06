# 17. Letter Combinations of a Phone Number

## Problem statement

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that `1` does not map to any letters.

![telephone_keypad](17_Telephone_keypad2.png)

 

### Example 1
```plain
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
```

### Example 2
```plain
Input: digits = ""
Output: []
```

### Example 3
```plain
Input: digits = "2"
Output: ["a","b","c"]
``` 

### Constraints

* `0 <= digits.length <= 4`.
* `digits[i]` is a digit in the range `['2', '9']`.

## Solution: Recursive

If you know the combinations `result` of a string `digits`, what is the result of extending it one more digit?

**Answer**: The new result is constructed by adding each letter of the mapping of the new digit to each string of the `result`. 

### Example 1 and 3
Assume you have computed the result of `digits = "2"`, which is `["a","b","c"]`. 

To compute the result of `digits = "23"`, you add each letter of the mapping `'3' -> {'d', 'e', 'f'}` to each string `"a", "b", "c"`. 

You get the new result `["ad","ae","af","bd","be","bf","cd","ce","cf"]`.

### Code
```cpp
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
void combination(string& digits, unordered_map<char, vector<char> >& m, 
        int i, vector<string>& result) {
    if (i >= digits.length()) {
        return;
    }
    vector<string> newResult;
    if (result.empty()) {
        result= {""};
    }
    for (string& s : result) {
        for (auto c : m[digits[i]]) {
            newResult.push_back(s + c);
        }
    }
    result.swap(newResult);
    combination(digits, m, i + 1, result);
}
vector<string> letterCombinations(string digits) {
    unordered_map<char, vector<char> > m;
    m['2'] = {'a', 'b', 'c'};
    m['3'] = {'d', 'e', 'f'};
    m['4'] = {'g', 'h', 'i'};
    m['5'] = {'j', 'k', 'l'};
    m['6'] = {'m', 'n', 'o'};
    m['7'] = {'p', 'q', 'r', 's'};
    m['8'] = {'t', 'u', 'v'};
    m['9'] = {'w', 'x', 'y', 'z'};
    vector<string> result;
    combination(digits, m, 0, result);
    return result;
}
void printResult(vector<string>& result) {
    cout << "[";
    for (string& s : result) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<string> result = letterCombinations("23");
    printResult(result);
    result = letterCombinations("");
    printResult(result);
    result = letterCombinations("2");
    printResult(result);
}
```
```plain
Output:
[ad,ae,af,bd,be,bf,cd,ce,cf,]
[]
[a,b,c,]
```

### Complexity
* Runtime: `O(3^N)`, where `N = digits.length`.
* Extra space: `O(1)` (the map).

## References
* [https://leetcode.com/problems/letter-combinations-of-a-phone-number/](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)
* [http://www.leetsolve.com/17-letter-combinations-of-a-phone-number/](http://www.leetsolve.com/17-letter-combinations-of-a-phone-number/)