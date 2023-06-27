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

### Complexity
* Runtime: `O(logn)`.
* Extra space: `O(1)`.

## Solution 2: Mathematics and the constraints of the problem

A power of three must divide another bigger one, i.e. `3^x | 3^y` where `0 <= x <= y`.

Because the constraint of the problem is `n <= 2^31 - 1`, you can choose the biggest power of three in this range to test the others.

It is `3^19 = 1162261467`. The next power will exceed `2^31 = 2147483648`.

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

### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.




