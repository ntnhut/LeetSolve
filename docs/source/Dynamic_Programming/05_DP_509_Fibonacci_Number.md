# Fibonacci Number

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

### Code explanation

This solution computes the nth Fibonacci number using a recursive approach. Here's how the code works:

1. The code checks if `n` is less than or equal to 1. If `n` is 0 or 1, it returns `n` itself because the Fibonacci sequence starts with 0 and 1, and the nth Fibonacci number is equal to `n` for `n` less than or equal to 1.

2. If `n` is greater than 1, it calculates the `n`-th Fibonacci number by recursively calling the `fib` function for `n - 1` and `n - 2` and then adding the results. This recursive approach continues until `n` becomes 0 or 1, at which point it returns the respective value.


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

### Code explanation

This solution calculates the `n`-th Fibonacci number using dynamic programming and an array to store intermediate results. Here's a step-by-step explanation:

1. The code first checks if `n` is less than or equal to 1. If `n` is 0 or 1, it returns `n` because these are the base cases of the Fibonacci sequence.

2. For values of `n` greater than 1, it initializes a vector `f` of size `n + 1` to store the Fibonacci numbers from 0 to `n`.

3. It sets the initial values of `f[0]` and `f[1]` to 0 and 1, respectively, as these are the known base cases of the Fibonacci sequence.

4. Then, it enters a loop starting from `i = 2` up to `n`. In each iteration, it calculates the Fibonacci number at index `i` as the sum of the two previous Fibonacci numbers, `f[i - 1]` and `f[i - 2]`, and stores it in `f[i]`.

5. After the loop completes, it returns `f[n]`, which contains the nth Fibonacci number.

### Complexity
This solution uses dynamic programming to avoid redundant calculations by storing and reusing previously computed Fibonacci numbers. It has a time complexity of `O(n)` because it iterates through the values from 2 to `n` once, calculating each Fibonacci number once. Additionally, it has a space complexity of `O(n)` due to the `f` array used to store intermediate results.

* Runtime: `O(n)`.
* Extra space: `O(n)`.

## Solution 3: Reduce space for dynamic programming

### Code
```cpp
#include <iostream>
#include <vector>
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    int f0 = 0;
    int f1 = 1;
    for (int i = 2; i <= n; i++) {
        int f2 = f1 + f0;
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

### Code explanation

This solution calculates the nth Fibonacci number iteratively using two variables to keep track of the last two Fibonacci numbers. Here's a step-by-step explanation:

1. The code first checks if `n` is less than or equal to 1. If `n` is 0 or 1, it returns `n` because these are the base cases of the Fibonacci sequence.

2. For values of `n` greater than 1, it initializes three integers: `f0`, `f1`, and `f2`. `f0` is initialized to 0, `f1` to 1, and `f2` will be used to store the current Fibonacci number.

3. It enters a loop starting from `i = 2` up to `n`. In each iteration:
   - It calculates the next Fibonacci number `f2` by adding `f1` and `f0`.
   - It updates `f0` to be the previous `f1`, which will be used in the next iteration.
   - It updates `f1` to be the previous `f2`, which will be used in the next iteration.

4. After the loop completes, it returns `f1`, which contains the nth Fibonacci number.

### Complexity
This solution effectively calculates the Fibonacci sequence without the need for an array to store intermediate results. It has a time complexity of `O(n)` because it iterates through the values from 2 to `n` once, calculating each Fibonacci number once. It also has a space complexity of `O(1)` because it uses only a constant amount of additional memory to store the variables `f0`, `f1`, and `f2`.

* Runtime: `O(n)`.
* Extra space: `O(1)`.


