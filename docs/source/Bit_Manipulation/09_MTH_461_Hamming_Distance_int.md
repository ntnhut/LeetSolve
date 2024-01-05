# Hamming Distance

## [Problem statement](https://leetcode.com/problems/hamming-distance/)
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

### Code explanation

1. The code first calculates the bitwise XOR (`^`) of `x` and `y` and stores the result in the variable `z`. This step effectively flips all the bits in `z` where `x` and `y` have different values and leaves the bits that are the same in both numbers unchanged.

2. It initializes a variable `count` to 0. This variable will be used to count the number of set (1) bits in the binary representation of `z`.

3. It enters a `while` loop that continues as long as `z` is not equal to 0 (meaning there are still bits to process).

4. Inside the loop, it checks the least significant bit of `z` by performing a bitwise AND operation with 1 (`z & 1`). If the result of this operation is 1, it means that the least significant bit of `z` is set (1), so it increments the `count` variable.

5. It then shifts the bits of `z` to the right by one position (`z = z >> 1`). This step effectively moves to the next bit position in `z` for examination.

6. The loop continues this process, checking each bit of `z`, incrementing `count` for each set bit, and shifting `z` until all bits have been processed.

7. Finally, the function returns the value of `count`, which represents the Hamming distance between `x` and `y`.

In summary, this code calculates the Hamming distance by XORing the two integers to find their differences and then counts the number of set bits (1s) in the XOR result, which corresponds to the positions where the two numbers differ in binary representation.

### Complexity
* Runtime: `O(1)` as the number of bits is at most 32 as constrained.
* Extra space: `O(1)`.




