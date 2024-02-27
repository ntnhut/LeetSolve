# Hamming Distance
% Easy 

## Problem statement

[^url]The [Hamming distance](https://en.wikipedia.org/wiki/Hamming_distance) between two integers is the number of positions at which the corresponding bits are different.

Given two integers `x` and `y`, return the **Hamming distance** between them.

[^url]: https://leetcode.com/problems/hamming-distance/

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

### Example 1
```text
x = 1   (0 0 0 1)
y = 4   (0 1 0 0)
z = x^y (0 1 0 1)
```

### Code
```cpp
#include <iostream>
int hammingDistance(int x, int y) {
    // compute the bit difference 
    int z = x ^ y;
    int count = 0;
    while (z) {
        count += z & 1; // e.g. '0101' & '0001'
        // shift z to the right one position
        z = z >> 1; // e.g. z = '0101' >> '0010'
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

### Complexity
* Runtime: `O(1)` as the number of bits is at most 32 as constrained.
* Extra space: `O(1)`.

## Conclusion

Utilizing bitwise operations, such as XOR (^) and bitwise AND (&), allows for efficient computation of the Hamming distance between two integers. This approach provides a straightforward and efficient method for calculating the Hamming distance without the need for complex logic or additional data structures.

## Exercise
- [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)

