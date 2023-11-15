# Roman to Integer

## [Problem statement](https://leetcode.com/problems/roman-to-integer/)

Roman numerals utilize seven symbols: `I`, `V`, `X`, `L`, `C`, `D`, and `M` to represent numbers. 

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
int romanToInt(string s) 
{
    unordered_map<char, int> value = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    int result = value[s.back()];
    for (int i = s.length() - 2; i >= 0; i--) 
    {
        if (value[s[i]] < value[s[i+1]])
        {
            result -= value[s[i]];
        }
        else
        {
            result += value[s[i]];
        }
    }
    return result;
}
int main() 
{
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

### Code explanation

1. This code initializes an unordered map `value` that maps Roman numeral characters to their integer values. Each key-value pair represents a Roman numeral character and its corresponding integer value.

2. It initializes the `result` variable with the integer value of the last character in the Roman numeral string `s`. This serves as the starting point for the total value.

3. The main processing is done in a `for` loop that iterates through the Roman numeral string from the second-to-last character (index `s.length() - 2`) and goes backward to the beginning of the string (index `0`).

4. Inside the loop, the code compares the value of the current Roman numeral character (`s[i]`) with the value of the next Roman numeral character (`s[i+1]`):
   - If the value of the current character is less than the value of the next character, it means that the current character represents a subtractive combination (e.g., IV for 4 or IX for 9). In this case, subtract the value of the current character from the `result`.
   - If the value of the current character is greater than or equal to the value of the next character, it means that the current character represents an additive combination (e.g., III for 3 or XX for 20). In this case, add the value of the current character to the `result`.

5. The result is updated in each iteration of the loop based on the comparison, and the loop continues until it processes all characters in the string.

6. Finally, the function returns the `result`, which contains the total integer value corresponding to the Roman numeral string.


### Complexity
This solution efficiently converts a Roman numeral string into an integer by iterating through the string from right to left and applying the rules of Roman numerals, where subtractive combinations are subtracted and additive combinations are added to calculate the total value. The unordered map is used to look up the values of Roman numerals. 

* Runtime: `O(N)` where `N = s.length`.
* Extra space: `O(1)`.



