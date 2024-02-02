# Concatenation of Consecutive Binary Numbers

## [Problem statement](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)

Given an integer `n`, return the decimal value of the binary string formed by concatenating the binary representations of `1` to `n` in order, modulo `10^9 + 7`.

### Example 1
```text
Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 
```

### Example 2
```text
Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
```

### Example 3
```text
Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 10^9 + 7, the result is 505379714.
``` 

### Constraints

* `1 <= n <= 10^5`.

## Solution: Recursive

There must be some relationship between the result of `n` and the result of `n - 1`. 

First, let us list some first values of `n`.

* For `n = 1`: the final binary string is `"1"`, its decimal value is `1`.
* For `n = 2`: the final binary string is `"110"`, its decimal value is `6`.
* For `n = 3`: the final binary string is `"11011"`, its decimal value is `27`.

Look at `n = 3`, you can see the relationship between the decimal value of `"11011"` and the one of `"110"` (of `n = 2`) is:

```text
27 = 6 * 2^2 + 3
Dec("11011") = Dec("110") * 2^num_bits("11") + Dec("11")
Result(3) = Result(2) * 2^num_bits(3) + 3.
```

The same equation for `n = 2`:

```text
6 = 1 * 2^2 + 2
Dec("110") = Dec("1") * 2^num_bits("10") + Dec("10")
Result(2) = Result(1) * 2^num_bits(2) + 2.
```

In general, the recursive relationship between `n` and `n - 1` is:

```text
Result(n) = Result(n - 1) * 2^num_bits(n) + n.
```

### Code
```cpp
#include <cmath>
#include <iostream>
int concatenatedBinary(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        const int num_bits = std::log2(i) + 1;        
        result = ((result << num_bits) + i) % 1000000007;
    }
    return result;
}
int main() {
    std::cout << concatenatedBinary(1) << std::endl;
    std::cout << concatenatedBinary(3) << std::endl;
    std::cout << concatenatedBinary(12) << std::endl;
}
```
```text
Output:
1
27
505379714
```

This solution efficiently calculates the concatenated binary representation of integers from `1` to `n`, using bitwise operations and modular arithmetic. 

### Complexity
The time complexity is `O(n*logn)`, where `n` is the input integer, making it a reasonably efficient solution.

* Runtime: `O(n*logn)`.
* Extra space: `O(1)`.




