# Power of Three
% Easy
## Problem statement

[^url]Given an integer `n`, return `true` if it is a power of three. Otherwise, return `false`.

An integer `n` is a power of three, if there exists an integer `x` such that `n == 3^x`.

[^url]: https://leetcode.com/problems/power-of-three/

### Example 1
```text
Input: n = 27
Output: true
Explanation: 27 = 3^3.
```

### Example 2
```text
Input: n = 0
Output: false
Explanation: There is no x where 3^x = 0.
```

### Example 3
```text
Input: n = -1
Output: false
Explanation: There is no x where 3^x = (-1).
``` 

### Constraints

* `-2^31 <= n <= 2^31 - 1`.
 

### Follow up
* Could you solve it without loops/recursion?

## Solution 1: Repeat the division

### Code
```cpp
#include <iostream>
using namespace std;
bool isPowerOfThree(int n) {
    while (n % 3 == 0 && n > 0) {
        n /= 3;
    }
    return n == 1;
}
int main() {
    cout << isPowerOfThree(27) << endl;
    cout << isPowerOfThree(0) << endl;
    cout << isPowerOfThree(-1) << endl;
}
```
```text
Output:
1
0
0
```
This solution repeatedly divides the input by 3 until it either becomes 1 (indicating that it was a power of three) or cannot be divided further by 3.

### Complexity
* Runtime: `O(logn)`.
* Extra space: `O(1)`.

## Solution 2: Mathematics and the constraints of the problem

A power of three must divide another bigger one, i.e. $3^x | 3^y$ where $0 \leq x \leq y$.

Because the constraint of the problem is $n \leq 2^{31} - 1$, you can choose the biggest power of three in this range to test the others.

It is $3^{19} = 1162261467$. The next power will exceed $2^{31} = 2147483648$.

### Code
```cpp
#include <iostream>
using namespace std;
bool isPowerOfThree(int n) {
    return n > 0 && 1162261467 % n == 0;
}
int main() {
    cout << isPowerOfThree(27) << endl;
    cout << isPowerOfThree(0) << endl;
    cout << isPowerOfThree(-1) << endl;
}
```
```text
Output:
1
0
0
```

This solution effectively checks whether `n` is a power of three by verifying if it is a divisor of the largest power of three that fits within 32 bits. If the condition is met, it returns `true`, indicating that `n` is a power of three; otherwise, it returns `false`.

### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.

## Readable code

Though Solution 2 offers a direct approach without the need for iteration, it is not easy to understand like Solution 1, where complexity of `O(logn)` is not too bad.

## Exercise
- Check if Number is a Sum of Powers of Three[^ex].

[^ex]: https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/