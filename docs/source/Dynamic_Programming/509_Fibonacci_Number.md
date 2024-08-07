# {index}`Fibonacci Number`

## [Problem statement](https://leetcode.com/problems/fibonacci-number/)

The Fibonacci numbers make up a sequence denoted as `F(n)`, known as the Fibonacci sequence. Each number in this sequence is the sum of the two preceding numbers, with the sequence starting from `0` and `1`. In other words:

```text
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
```

Your task is to calculate the value of `F(n)` given an integer `n`. 



### Example 1
```text
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
```

### Example 2
```text
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
```

### Example 3
```text
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
``` 

### Constraints

* `0 <= n <= 30`.

## Solution 1: Recursive

### Code
```cpp
#include <iostream>
int fib(int n) {
    if (n <= 1) {
        return n;
    } 
    return fib(n - 1) + fib(n - 2);
}
int main() {
    std::cout << fib(2) << std::endl;
    std::cout << fib(3) << std::endl;
    std::cout << fib(4) << std::endl;
}
```
```text
Output:
1
2
3
```

This solution computes the nth Fibonacci number using a recursive approach. 

### Complexity
The time complexity of this solution is exponential, specifically `O(2^n)`. This is because it repeatedly makes two recursive calls for each `n`, resulting in an exponential number of function calls and calculations. As `n` grows larger, the execution time increases significantly. 

The space complexity of the given recursive Fibonacci solution is `O(n)`. This space complexity arises from the function call stack when making recursive calls.

When you call the `fib` function with a value of `n`, it generates a call stack with a depth of `n`, as each call to `fib` leads to two more recursive calls (one for `n - 1` and one for `n - 2`) until `n` reaches the base cases (0 or 1). The space required to store the function call stack is proportional to the depth of the recursion, which is `n`.

Therefore, the space complexity is linearly related to the input value `n`, making it `O(n)`. This can be a concern for large values of `n` because it could lead to a stack overflow if `n` is too large. 

* Runtime: `O(2^n)`.
* Extra space: `O(n)`.

## Solution 2: Dynamic programming
```cpp
#include <iostream>
#include <vector>
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    // store all computed Fibonacci numbers
    std::vector<int> f(n + 1);
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    return f[n];
}
int main() {
    std::cout << fib(2) << std::endl;
    std::cout << fib(3) << std::endl;
    std::cout << fib(4) << std::endl;
}
```
```text
Output:
1
2
3
```

This solution uses dynamic programming to avoid redundant calculations by storing and reusing previously computed Fibonacci numbers.

### Complexity

* Runtime: `O(n)`.
* Extra space: `O(n)`.

## Solution 3: Reduce space for dynamic programming

### Code
```cpp
#include <iostream>
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    // store only two previous Fibonacci numbers
    int f0 = 0;
    int f1 = 1;
    for (int i = 2; i <= n; i++) {
        int f2 = f1 + f0;
        // update for next round
        f0 = f1;
        f1 = f2;
    }
    return f1;
}
int main() {
    std::cout << fib(2) << std::endl;
    std::cout << fib(3) << std::endl;
    std::cout << fib(4) << std::endl;
}
```
```text
Output:
1
2
3
```

This solution calculates the nth Fibonacci number iteratively using two variables to keep track of the last two Fibonacci numbers. 

### Complexity

* Runtime: `O(n)`.
* Extra space: `O(1)`.

## Conclusion

The Fibonacci sequence can be efficiently computed using various techniques, including recursion with memoization, bottom-up dynamic programming, or even optimizing space usage by storing only the necessary previous Fibonacci numbers. 

Solutions 2 and 3 demonstrate dynamic programming approaches, where Fibonacci numbers are computed iteratively while storing intermediate results to avoid redundant computations. 

Solution 3 further optimizes space usage by only storing the necessary previous Fibonacci numbers, resulting in a space complexity of `O(1)`. Understanding these different approaches and their trade-offs is essential for selecting the most appropriate solution based on the problem constraints and requirements.

## Exercise
- [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/).

