## 1680. Concatenation of Consecutive Binary Numbers

### Problem statement

Given an integer `n`, return the decimal value of the binary string formed by concatenating the binary representations of `1` to `n` in order, modulo `10^9 + 7`.

#### Example 1
```plain
Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 
```

#### Example 2
```plain
Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
```

#### Example 3
```plain
Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 10^9 + 7, the result is 505379714.
``` 

#### Constraints

* `1 <= n <= 10^5`.

### Solution: Recursive

There must be some relationship between the result of `n` and the result of `n - 1`. 

First, let us list some first values of `n`.

* For `n = 1`: the final binary string is `"1"`, its decimal value is `1`.
* For `n = 2`: the final binary string is `"110"`, its decimal value is `6`.
* For `n = 3`: the final binary string is `"11011"`, its decimal value is `27`.

Look at `n = 3`, you can see the relationship between the decimal value of `"11011"` and the one of `"110"` (of `n = 2`) is:

```plain
Dec("11011") = Dec("110") * 2^2 + 3.
```

The same equation for `n = 2`:

```plain
Dec("110") = Dec("1") * 2^2 + 2.
```

The exponents `2` of `2^2` in the relationships above are the number of bits of `n = 3` and `n = 2`.

In general, the recursive relationship between `n` and `n - 1` is:

```plain
Dec("Bin(1)..Bin(n)") = Dec("Bin(1).. Bin(n - 1)") * 2^num_bits(n) + n.
```

#### Code
```cpp
#include <cmath>
#include <iostream>
int concatenatedBinary(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        const int bits = std::log2(i) + 1;        
        result = ((result << bits) + i) % 1000000007;
    }
    return result;
}
int main() {
    std::cout << concatenatedBinary(1) << std::endl;
    std::cout << concatenatedBinary(3) << std::endl;
    std::cout << concatenatedBinary(12) << std::endl;
}
```
```plain
Output:
1
27
505379714
```

#### Complexity
* Runtime: `O(n)`.
* Extra space: `O(1)`.

### References
* [https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)
* [https://www.leetsolve.com/1680-concatenation-of-consecutive-binary-numbers](https://www.leetsolve.com/1680-concatenation-of-consecutive-binary-numbers)