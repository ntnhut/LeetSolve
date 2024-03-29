## 13. Roman to Integer

### Problem statement
Roman numerals are represented by seven symbols: `I`, `V`, `X`, `L`, `C`, `D`, and `M`.

```plain
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is written as `II` in Roman numeral, just two ones added together. `12` is written as `XII`, which is simply `X + II`. The number `27` is written as `XXVII`, which is `XX + V + II`.

Roman numerals are usually written from largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

* `I` can be placed before `V` (`5`) and `X` (`10`) to make `4` and `9`. 
* `X` can be placed before `L` (`50`) and `C` (`100`) to make `40` and `90`. 
* `C` can be placed before `D` (`500`) and `M` (`1000`) to make `400` and `900`.

Given a Roman numeral, convert it to an integer.


#### Example 1
```plain
Input: s = "III"
Output: 3
Explanation: III = 3.
```
#### Example 2
```plain
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V = 5, III = 3.
```

#### Example 3
```plain
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
``` 

#### Constraints

* `1 <= s.length <= 15`.
* `s` contains only the characters `'I'`, `'V'`, `'X'`, `'L'`, `'C'`, `'D'`, `'M'`.
* It is guaranteed that `s` is a valid roman numeral in the range `[1, 3999]`.

### Solution 1: Mapping and summing the values

And to treat the subtraction cases easier, you can iterate the string `s` backward.

#### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
int romanToInt(string s) {
    unordered_map<char, int> value = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    int i = s.length() - 1;
    int result = value[s[i--]];
    while (i >= 0) {
        if (value[s[i]] < value[s[i+1]]) {
            result -= value[s[i--]]; 
        } else {
            result += value[s[i--]];
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
```plain
Output:
3
58
1994
```

#### Complexity
* Runtime: `O(N)` where `N = s.length`.
* Extra space: `O(1)` (the map `value` is very small).

### Solution 2: Move the unchanged map out of the function

Whenever `romanToInt()` is called for each value of `s`, the same map `value` is recreated. You should only create it one time if you call `romanToInt()` many times. 

#### Code
```cpp
#include <iostream>
#include <unordered_map>
using namespace std;
const unordered_map<char, int> value = {
    {'I', 1},
    {'V', 5},
    {'X', 10},
    {'L', 50},
    {'C', 100},
    {'D', 500},
    {'M', 1000}
};
int romanToInt(string s) {
    int i = s.length() - 1;
    int result = value.at(s[i--]);
    while (i >= 0) {
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
```plain
Output:
3
58
1994
```

#### Complexity
* Runtime: `O(N)` where `N = s.length`.
* Extra space: `O(1)`.

### C++ notes
* Because the map `value` is unchanged, it should be `const`. Then you must use method `at()` to access its `const` values (see the notes of its operator [`[]`](https://en.cppreference.com/w/cpp/container/unordered_map/operator_at)).

### Conclusion

As the problem is about encoding/decoding between a string and an integer, you could you an [unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map) here.

This is a very interesting problem since it is about history and mathematics. You can read more about it on [Wikipedia](https://en.wikipedia.org/wiki/Roman_numerals).

What is your solution to this problem? Check the correction and the performance of your code at [leetcode.com](https://leetcode.com/problems/roman-to-integer/).