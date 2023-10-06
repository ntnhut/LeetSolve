# Partitioning Into Minimum Number Of Deci-Binary Numbers

## [Problem statement](https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/)

A decimal number is called deci-binary if each of its digits is either `0` or `1` without any leading zeros. For example, `101` and `1100` are deci-binary, while `112` and `3001` are not.

Given a string `n` that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to `n`.

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
int minPartitions(string n) {
    char maxDigit = '0';
    for (char& d : n) {
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

### Code explanation

1. The code initializes a variable `maxDigit` to '0'. This variable will be used to keep track of the maximum digit encountered.

2. It iterates through each character `d` in the string `n`.

3. For each character `d`, the code compares it with the current `maxDigit`. If `d` is greater than `maxDigit`, it updates `maxDigit` to `d`. This step ensures that `maxDigit` always holds the maximum digit encountered in the string.

4. After the loop finishes, `maxDigit` will contain the maximum digit present in the string `n`.

5. The code returns the integer value of `maxDigit - '0'`. Since `maxDigit` is a character representing a digit, subtracting '0' converts it to its integer value.

In summary, the code identifies the maximum digit in the input string `n` and returns it as the minimum number of partitions required, considering each digit as a separate partition.
### Complexity
* Runtime: `O(N)`, where `N = n.length`.
* Extra space: `O(1)`.


