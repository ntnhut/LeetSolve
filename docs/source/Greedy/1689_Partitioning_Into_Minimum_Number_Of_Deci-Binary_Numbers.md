# Partitioning Into Minimum Number Of Deci-Binary Numbers
% Medium

## Problem statement

[^url]A decimal number is called deci-binary if each of its digits is either `0` or `1` without any leading zeros. For example, `101` and `1100` are deci-binary, while `112` and `3001` are not.

Given a string `n` that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to `n`.

[^url]: https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/

### Example 1
```text
Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32
```

### Example 2
```text
Input: n = "82734"
Output: 8
```

### Example 3
```text
Input: n = "27346209830709182346"
Output: 9
``` 

### Constraints

* `1 <= n.length <= 10^5`.
* `n` consists of only digits.
* `n` does not contain any leading zeros and represents a positive integer.

## Solution: Identify the maximum digit of `n`

Any digit `d` can be obtained by summing the digit `1` `d` times.

The problem turns into identifying the maximum digit of `n`.

### Example 2
For `n = "82734"` the answer is 8 because:

```text
  82734
= 11111 
+ 11111 
+ 10111 
+ 10101 
+ 10100
+ 10100
+ 10100
+ 10000
```

### Code
```cpp
#include <iostream>
using namespace std;
int minPartitions(const string& n) {
    char maxDigit = '0';
    for (auto& d : n) {
        maxDigit = max(maxDigit, d);
    }
    return maxDigit - '0';
}
int main() {
    cout << minPartitions("32") << endl;
    cout << minPartitions("82734") << endl;
    cout << minPartitions("27346209830709182346") << endl;
}
```
```text
Output:
3
8
9
```


### Complexity
* Runtime: `O(N)`, where `N = n.length`.
* Extra space: `O(1)`.

## Conclusion

This problem can be efficiently solved by identifying the maximum digit in the string. Since each deci-binary number can only contain digits from 0 to 9, the maximum digit determines the minimum number of deci-binary numbers needed. 

By finding the maximum digit in the string and converting it to an integer, the solution effectively determines the minimum number of deci-binary numbers required.