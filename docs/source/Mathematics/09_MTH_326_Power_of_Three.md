# Power of Three

## [Problem statement](https://leetcode.com/problems/power-of-three/)
Given an integer `n`, return `true` if it is a power of three. Otherwise, return `false`.

An integer `n` is a power of three, if there exists an integer `x` such that `n == 3^x`.


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
 

**Follow up**: Could you solve it without loops/recursion?

## Solution 1: Recursion

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
### Code explanation

1. The code enters a while loop that continues as long as `n` is greater than zero and divisible by 3 (`n % 3 == 0`).
2. In each iteration of the loop, it divides `n` by 3 (`n /= 3`) to reduce it towards 1.
3. Finally, after exiting the loop, it checks if `n` is equal to 1. If `n` is 1, it means that the original input was a power of three, and the function returns `true`. Otherwise, it returns `false`.

Essentially, this code repeatedly divides the input by 3 until it either becomes 1 (indicating that it was a power of three) or cannot be divided further by 3.

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

### Code explanation

1. `n > 0`: This condition ensures that we are only considering positive integers. Powers of three are positive integers, so this is a necessary condition.

2. `1162261467 % n == 0`: This part of the condition is where the magic happens. The number `1162261467` is the largest power of three that can be represented using 32 bits (`3^19`). 

   When we take any power of three less than or equal to this value and calculate the modulus with it (`1162261467 % n`), the result will be zero if and only if `n` is a power of three. This is because powers of three have no factors other than 3 in their prime factorization.

So, the code effectively checks whether `n` is a power of three by verifying if it is a divisor of the largest power of three that fits within 32 bits. If the condition is met, it returns `true`, indicating that `n` is a power of three; otherwise, it returns `false`.

### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.
