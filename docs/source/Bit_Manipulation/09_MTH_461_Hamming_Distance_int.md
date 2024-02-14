# Hamming Distance
% Easy https://leetcode.com/problems/hamming-distance/

## Problem statement
The [Hamming distance](https://en.wikipedia.org/wiki/Hamming_distance) between two integers is the number of positions at which the corresponding bits are different.

Given two integers `x` and `y`, return the **Hamming distance** between them.

### Example 1
```text
Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ^   ^
The above arrows point to positions where the corresponding bits are different.
```

### Example 2
```text
Input: x = 3, y = 1
Output: 1
```
 

### Constraints

* `0 <= x, y <= 2^31`.

## Solution: Using bitwise operator XOR
You could use {index}`bitwise XOR` (`^`) to get the bit positions where `x` and `y` are different. Then use {index}`bitwise AND` operator (`&`) at each position to count them.

### Code
```cpp
#include <iostream>
int hammingDistance(int x, int y) {
    int z = x ^ y;
    int count = 0;
    while (z) {
        count += z & 1;
        z = z >> 1;
    }
    return count;
}
int main() {
    std::cout << hammingDistance(1,4) << std::endl; // 2
    std::cout << hammingDistance(1,3) << std::endl; // 1
}
```
```text
Output:
2
1
```

This solution calculates the Hamming distance by XORing the two integers to find their differences and then counts the number of set bits (1s) in the XOR result, which corresponds to the positions where the two numbers differ in binary representation.

### Complexity
* Runtime: `O(1)` as the number of bits is at most 32 as constrained.
* Extra space: `O(1)`.

## Exercise
- [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)

