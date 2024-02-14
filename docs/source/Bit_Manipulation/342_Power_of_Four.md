# Power of Four
% Easy 
## Problem statement

[^url]Given an integer `n`, return `true` if it is a power of four. Otherwise, return `false`.

An integer `n` is a power of four if there exists an integer `x` such that `n == 4^x`.

[^url]: https://leetcode.com/problems/power-of-four/ 

### Example 1
```text
Input: n = 16
Output: true
```

### Example 2
```text
Input: n = 5
Output: false
```

### Example 3
```text
Input: n = 1
Output: true
``` 

### Constraints

* `-2^31 <= n <= 2^31 - 1`.
 

**Follow up**: Could you solve it without loops/recursion?

## Solution 1: Division by four

### Code
```cpp
#include <iostream>
using namespace std;
bool isPowerOfFour(int n) {
    while (n % 4 == 0 && n > 0) {
        n /= 4;
    }
    return n == 1;
}
int main() 
{
    cout << isPowerOfFour(16) << endl;
    cout << isPowerOfFour(5) << endl;
    cout << isPowerOfFour(1) << endl;
}
```
```text
Output:
1
0
1
```

This solution repeatedly divides the given number `n` by 4 until `n` becomes either 1 or a number that is not divisible by 4. If `n` becomes 1 after this process, it means that `n` was originally a power of 4. 

### Complexity
* Runtime: `O(logn)`.
* Extra space: `O(1)`.

## Solution 2: Binary representation

You can write down the binary representation of the powers of four to find the pattern.

```text
1   : 1
4   : 100
16  : 10000
64  : 1000000
256 : 100000000
...
```

You might notice the patterns are **n is a positive integer having only one bit `1` in its binary representation and it is located at the odd positions** (starting from the right).

How can you formulate those conditions?

If `n` has only one bit `1` in its binary representation `10...0`, then `n - 1` has the complete opposite binary representation `01...1`. 

You can use the bit operator AND to formulate this condition
```text
n & (n - 1) == 0
``` 

Let `A` be the number whose binary representation has only bits `1` at all odd positions, then `n & A` is never `0`.

In this problem, `A < 2^31`. You can choose`A = 0x55555555`, the hexadecimal of `0101 0101 0101 0101 0101 0101 0101 0101`.

### Code
```cpp
#include <iostream>
using namespace std;
bool isPowerOfFour(int n) {
    return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
}
int main() {
    cout << isPowerOfFour(16) << endl;
    cout << isPowerOfFour(5) << endl;
    cout << isPowerOfFour(1) << endl;
}
```
```text
Output:
1
0
1
```
### Code explanation

This code checks whether an integer `n` is a power of four or not using bitwise operations.

Here's how the code works:

1. The condition `n > 0` checks if `n` is a positive integer because powers of four are positive integers.

2. `(n & (n - 1)) == 0`: This part checks if `n` is a power of two. When an integer is a power of two, it has only one bit set in its binary representation. For example, 2 is `10` in binary, 4 is `100`, 8 is `1000`, and so on. When you subtract 1 from these numbers, you get `01`, `11`, `111`, etc., respectively. The `&` ({index}`bitwise AND`) operation between `n` and `n - 1` will result in 0 if `n` is a power of two.

3. `(n & 0x55555555) != 0`: This part checks if the single set bit in `n` (if `n` is a power of two) is at an odd position. In binary, `0x55555555` is `01010101010101010101010101010101`, which has alternating `1`s and `0`s. This condition ensures that the single set bit in `n` is at an odd position, which is required for it to be a power of four.

So, the code returns `true` if `n` is a positive integer that is both a power of two and has its single set bit at an odd position, indicating that it's a power of four. Otherwise, it returns `false`.

### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.

## Exercise
- [Power of Two](https://leetcode.com/problems/power-of-two/)