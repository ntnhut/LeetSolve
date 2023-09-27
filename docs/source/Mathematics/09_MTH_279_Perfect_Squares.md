# Perfect Squares

## [Problem statement](https://leetcode.com/problems/perfect-squares/)
Given an integer `n`, return the least number of perfect square numbers that sum to `n`.

A **perfect square** is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, `1`, `4`, `9`, and `16` are perfect squares while `3` and `11` are not.

### Example 1
```text
Input: n = 9
Output: 1
Explanation: 9 is already a perfect square.
```
### Example 2
```text
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
```
### Example 3
```text
Input: n = 7
Output: 4
Explanation: 7 = 4 + 1 + 1 + 1.
```
### Example 4
```text
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
```

### Constraints

* `1 <= n <= 10^4`.

## Solution 1: Dynamic Programming
Let us call the function to be computed `numSquares(n)`, which calculates the least number of perfect squares that sum to `n`.

Here are the findings.
1. If `n` is already a perfect square then `numSquares(n) = 1`.
2. Otherwise, it could be written as `n = 1 + (n-1)`, or `n = 4 + (n-4)`, or `n = 9 + (n-9)`, etc. which means `n` is a sum of a perfect square (`1, 4` or `9`, etc.) and another number `m < n`. That leads to the problems `numSquares(m)` of smaller values `m`.
3. If you have gotten the results of the smaller problems `numSquares(n-1)`, `numSquares(n-4)`, `numSquares(n-9)`, etc. then `numSquares(n) = 1 + the minimum of those results`.

### Example 4
`n = 12` is not a perfect square. It can be written as `n = 1 + 11 = 4 + 8 = 9 + 3`.
- For `m = 11`, it is not a perfect square and can be written as `m = 1 + 10 = 4 + 7 = 9 + 2`.
- For `m = 8`, it is not a perfect square and can be written as `m = 1 + 7 = 4 + 4` (matched). You get `numSquares(8) = 2`.
- For `m = 3`, it is not a perfect square and can be written as `m = 1 + 2`.

You can continue to compute `numSquares(m)` for other values `m` in this recursive process. But you can see the case of `m = 8` was already the best solution. And `numSquares(12) = 1 + numSquares(8) = 1 + 2 = 3`, which is the case of `n = 12 = 4 + 4 + 4`.

To improve runtime, you can apply *dynamic programming* to cache the `numSquares(n)` that you have computed.

### Code
```cpp
#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;
int nsq(int n, unordered_map<int, int>& ns) {
    auto it = ns.find(n);
    if (it != ns.end()) {
        return it->second;
    }
    const int sq = sqrt(n);
    if (sq * sq == n) {
        ns[n] = 1;
        return 1;
    }
    int result = n;
    for (int i = 1; i <= sq; i++) {
        result = min(result, nsq(n - i*i, ns));
    }
    ns[n] = result + 1;
    return ns[n];
}
int numSquares(int n) {
    unordered_map<int, int> ns;
    return nsq(n, ns);
}
int main() {
    cout << numSquares(12) << endl;
    cout << numSquares(13) << endl;
}
```
```text
Output:
3
2
```

### Code explanation

1. `int nsq(int n, unordered_map<int, int>& ns)` is a recursive helper function that calculates the minimum number of perfect square numbers that sum up to the given integer `n`. It uses dynamic programming and memoization to avoid redundant calculations.

2. Inside `nsq`, the function first checks if the result for the value `n` is already calculated and stored in the `unordered_map` `ns`. If it is, the function returns the stored result directly, avoiding redundant calculations.

3. If the result for `n` is not found in `ns`, the function proceeds to calculate it. It does this by iterating through all the perfect square numbers starting from 1 (i.e., 1^2, 2^2, 3^2, ...) up to the largest perfect square less than or equal to `n`. For each perfect square number `i^2`, it recursively calls `nsq` with the remaining value `n - i^2`.

4. The function keeps track of the minimum number of perfect squares required to sum up to `n`. This minimum is initially set to `n`, as it can be represented by `n` perfect squares of 1.

5. After iterating through all possible perfect squares, the function stores the calculated minimum in the `ns` map for future reference and returns it plus 1. This `+1` represents the perfect square value that was subtracted to reach the minimum.

6. `int numSquares(int n)` is the main function that initializes an `unordered_map` called `ns` to store computed results and calls the helper function `nsq` with the given input `n`.

### Complexity
The key idea of this algorithm is to build the solution incrementally, starting from the smallest perfect squares, and use memoization to store and retrieve intermediate results. By doing this, it efficiently finds the minimum number of perfect squares required to sum up to `n`. The time complexity of this solution is `O(n*sqrt(n))` due to the nested loops and recursive calls, and the space complexity is `O(n)` for the memoization map `ns`.

* Runtime: `O(n*sqrt(n)) = O(n^(3/2))`.
* Extra space: `O(n)`.

## Solution 2: Number Theory
The dynamic programming solution above is good enough. But for those who are interested in Algorithmic Number Theory, there is a very interesting theorem that can solve the problem directly without recursion.

It is called [Lagrange's Four-Square Theorem](https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem), which states

> *every natural number can be represented as the sum of four integer squares.*

It was proven by Lagrange in 1770.
### Example 4
`n = 12 = 4 + 4 + 4 + 0` or `12 = 1 + 1 + 1 + 9`.

Applying to our problem, **`numSquares(n)` can only be 1, 2, 3, or 4. Not more.**

It turns into the problem of
> *identifying when `numSquares(n)` returns 1, 2, 3, or 4.*

Here are the cases.
1. If `n` is a perfect square, `numSquares(n) = 1`.
2. There is another theorem, [Legendre's Three-Square Theorem](https://en.wikipedia.org/wiki/Legendre%27s_three-square_theorem), which states that
`numSquares(n)` cannot be 1, 2, or 3 if `n` can be expressed as

$$
n = 4^a(8\cdot b + 7),
$$

where $a$, $b$ are nonnegative integers. 

In other words, `numSquares(n) = 4` if `n` is of this form.

### Example 3
$n = 7 = 4^0(8\cdot 0 + 7)$. It can only be written as `7 = 4 + 1 + 1 + 1`.

### Code
```cpp
#include <iostream>
#include <cmath>
using namespace std;
bool isSquare(int n) {
    int sq = sqrt(n);
    return sq * sq == n;
}
int numSquares(int n) {
    if (isSquare(n)) {
        return 1;
    }
    // Legendre's three-square theorem
    int m = n;
    while (m % 4 == 0) {
        m /= 4;
    }
    if (m % 8 == 7) {
        return 4;
    }
    const int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        if (isSquare(n - i*i)) {
            return 2;
        }
    }
    return 3;
}
int main() {
    cout << numSquares(12) << endl;
    cout << numSquares(13) << endl;
}
```
```text
Output:
3
2
```
### Code explanation

1. `bool isSquare(int n)` is a helper function that checks if an integer `n` is a perfect square. It calculates the square root of `n` using `sqrt(n)` and checks if the product of the square root (`sq`) with itself (`sq * sq`) equals `n`. If they are equal, it returns `true`, indicating that `n` is a perfect square; otherwise, it returns `false`.

2. In the `numSquares(int n)` function:
   - It first checks if the input `n` itself is a perfect square by calling the `isSquare` function. If `n` is a perfect square, the function returns `1` because it takes only one perfect square to represent `n`.

   - If `n` is not a perfect square, it proceeds to apply Legendre's three-square theorem to simplify the problem:
     - It initializes an integer `m` with the same value as `n`.
     - It repeatedly divides `m` by `4` as long as `m` is divisible by `4`. This step is based on Legendre's three-square theorem, which states that a positive integer can be represented as the sum of three perfect squares if and only if it is not in the form `4^a * (8b + 7)` for non-negative integers `a` and `b`. By dividing `m` by `4`, it ensures that `m` is not of the form `4^a * (8b + 7)`.
     - If `m` becomes `7` modulo `8`, it returns `4`. This is another condition from Legendre's three-square theorem, which states that if `m` leaves a remainder of `7` when divided by `8`, it cannot be represented as the sum of fewer than four perfect squares.

   - If neither of the above conditions is met, it proceeds with a loop from `1` to the integer square root of `n` (`sq`). Inside the loop, it checks if `n - i*i` is a perfect square by calling the `isSquare` function. If it finds such a perfect square, it returns `2` because `n` can be represented as the sum of two perfect squares (`i*i` and the perfect square found). This covers the case where `n` can be represented as `1 + 1 + ... + 1` (with `i` ones) plus a perfect square.

3. If none of the above conditions are met, it returns `3`. This means that `n` cannot be represented as the sum of fewer than three perfect squares and falls back to the default case.

### Complexity
In summary, the code efficiently finds the minimum number of perfect squares required to sum up to the given integer `n` by first applying mathematical properties and Legendre's three-square theorem to simplify the problem and then using a loop to find possible combinations of two perfect squares. The time complexity of this solution is `O(sqrt(n))`, and it does not require dynamic programming or memoization.

* Runtime: `O(sqrt(n)) = O(n^(1/2))`.
* Extra space: `O(1)`.

## Solution 3: Further performance improvement

Lagrange's Four-Square Theorem and Legendre's Three-Square Theorem are so powerful to solve this problem. But you can still do a little more algebra to improve further the runtime of the implementation above.

Instead of looping over `sqrt(n)` in the final `for` loop, we will prove that this loop over `sqrt(m)` is enough. That will improve runtime a lot since `m` is much less than `n`.

Let `m` be the reduced value of `n` after the Legendre's `while` loop. It satisfies

$$
n = 4^a \cdot m.
$$

We will prove that `numSquares(n) = numSquares(m)`.

In fact, if `m` is written as $m = x^2 + y^2 + z^2$, where $x$, $y$, $z$ are nonnegative integers. Then

$$
n = 4^a \cdot m = (2^a)^2 \cdot m = (2^a \cdot x)^2 + (2^a \cdot y)^2 + (2^a \cdot z)^2.
$$

In other words, `numSquares(n) = numSquares(m)`.

Now you can change directly the value `n` during the Legendre's `while` loop without affecting the final result. 


### Code
```cpp
#include <iostream>
#include <cmath>
using namespace std;
bool isSquare(int n) {
    int sq = sqrt(n);
    return sq * sq == n;
}
int numSquares(int n) {
    if (isSquare(n)) {
        return 1;
    }
    // Legendre's three-square theorem
    while (n % 4 == 0) {
        n /= 4;
    }
    if (n % 8 == 7) {
        return 4;
    }
    const int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        if (isSquare(n - i*i)) {
            return 2;
        }
    }
    return 3;
}
int main() {
    cout << numSquares(12) << endl;
    cout << numSquares(13) << endl;
}
```
```text
Output:
3
2
```
### Complexity
* Runtime: `O(sqrt(n)) = O(n^(1/2))`.
* Extra space: `O(1)`.

## Conclusion
- The title of this coding challenge (*Perfect squares*) gives you a hint it is more about mathematics than coding technique.
- It is amazing from Lagrange's Four-Square Theorem there are only four possibilities for the answer to the problem. Not many people knowing it.
- You can get an optimal solution to a coding problem when you know something about the mathematics behind it.

Hope you learn something interesting from this code challenge.

*Have fun with coding and mathematics!*


