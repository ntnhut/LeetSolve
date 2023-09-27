# Power of Four

## [Problem statement](https://leetcode.com/problems/power-of-four/)
Given an integer `n`, return `true` if it is a power of four. Otherwise, return `false`.

An integer `n` is a power of four if there exists an integer `x` such that `n == 4^x`.

 

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

1. The condition `n % 4 == 0` checks if `n` is a multiple of 4.

2. The condition `n > 0` ensures that we are only considering positive integers because powers of four are positive integers.

3. Inside the `while` loop, `n /= 4` is used to repeatedly divide `n` by 4 as long as both conditions (`n % 4 == 0` and `n > 0`) are satisfied. This division effectively removes one factor of 4 from `n` in each iteration.

4. After the `while` loop, if `n` has been reduced to 1, it means that `n` was originally a power of four. This is because repeatedly dividing a power of four by 4 will eventually lead to 1, and no other value will reach 1 under these conditions.

5. If `n` is not 1 after the loop, it means that it couldn't be divided by 4 to reach 1, indicating that `n` is not a power of four.

So, the code returns `true` if `n` is a power of four and `false` otherwise. It achieves this by checking divisibility by 4 and repeatedly dividing `n` by 4 until it reaches 1 or can no longer be divided evenly.

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

2. `(n & (n - 1)) == 0`: This part checks if `n` is a power of two. When an integer is a power of two, it has only one bit set in its binary representation. For example, 2 is `10` in binary, 4 is `100`, 8 is `1000`, and so on. When you subtract 1 from these numbers, you get `01`, `11`, `111`, etc., respectively. The `&` (bitwise AND) operation between `n` and `n - 1` will result in 0 if `n` is a power of two.

3. `(n & 0x55555555) != 0`: This part checks if the single set bit in `n` (if `n` is a power of two) is at an odd position. In binary, `0x55555555` is `01010101010101010101010101010101`, which has alternating `1`s and `0`s. This condition ensures that the single set bit in `n` is at an odd position, which is required for it to be a power of four.

So, the code returns `true` if `n` is a positive integer that is both a power of two and has its single set bit at an odd position, indicating that it's a power of four. Otherwise, it returns `false`.

### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.


