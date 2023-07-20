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

### Complexity
* Runtime: $O(\log n)$.
* Extra space: $O(1)$.

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

### Complexity
* Runtime: $O(1)$.
* Extra space: $O(1)$.


