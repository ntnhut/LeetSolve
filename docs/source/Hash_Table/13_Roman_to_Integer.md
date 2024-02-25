# Roman to Integer
% Easy
## Problem statement

[^url]Roman numerals utilize seven symbols: `I`, `V`, `X`, `L`, `C`, `D`, and `M` to represent numbers. 

```text
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is denoted as `II`, which is essentially two ones added together. Similarly, `12` is represented as `XII`, indicating `X + II`. The number `27` is written as `XXVII`, which stands for `XX + V + II`.

Roman numerals are generally written from the largest value to the smallest value, moving from left to right. However, there are exceptions to this pattern. For instance, the numeral for `4` is `IV` instead of `IIII`, where `I` is placed before `V` to subtract `1` from `5`. Similarly, `9` is `IX`, representing the subtraction of `1` from `10`. There are six such subtraction instances:

- `I` before `V` (`5`) or `X` (`10`) forms `4` and `9`.
- `X` before `L` (`50`) or `C` (`100`) forms `40` and `90`.
- `C` before `D` (`500`) or `M` (`1000`) forms `400` and `900`.

Your task is to convert a given Roman numeral into its equivalent integer value. 

[^url]: https://leetcode.com/problems/roman-to-integer/ 
### Example 1
```text
Input: s = "III"
Output: 3
Explanation: III = 3.
```
### Example 2
```text
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
```

### Example 3
```text
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
``` 

### Constraints

* `1 <= s.length <= 15`.
* `s` contains only the characters `'I'`, `'V'`, `'X'`, `'L'`, `'C'`, `'D'`, `'M'`.
* It is guaranteed that `s` is a valid Roman numeral in the range `[1, 3999]`.

## Solution: Mapping and summing the values

To treat the subtraction cases easier you can iterate the string `s` backward.

### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
const unordered_map<char, int> value = {
    {'I', 1},   {'V', 5},
    {'X', 10},  {'L', 50},
    {'C', 100}, {'D', 500},
    {'M', 1000}
};
int romanToInt(const string& s) {

    // starting from the end character of the string s
    int i = s.length() - 1;
    int result = value.at(s[i--]);
    while (i >= 0) {
        // In cases of subtraction
        if (value.at(s[i]) < value.at(s[i+1])) {
            result -= value.at(s[i--]); 
        } else {
            result += value.at(s[i--]);
        }
    }
    return result;
}
int main() {
    cout << romanToInt("III") << endl;
    cout << romanToInt("LVIII") << endl;
    cout << romanToInt("MCMXCIV") << endl;
}
```
```text
Output:
3
58
1994
```

### Complexity

* Runtime: `O(N)` where `N = s.length`.
* Extra space: `O(1)`.

## Key Takeaway

This problem can be solved using a map to store the values of each Roman numeral character. This solution iterates through the string from right to left, accumulating the integer value based on the corresponding Roman numeral characters. 

By comparing the current character's value with the previous one, the solution handles cases of subtraction (e.g., IV, IX, etc.) by subtracting the value if it's smaller and adding it otherwise.

## Exercise
- [Integer to Roman](https://leetcode.com/problems/integer-to-roman/)
