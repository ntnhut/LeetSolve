# Construct Target Array With Multiple Sums

## [Problem statement](https://leetcode.com/problems/construct-target-array-with-multiple-sums/)
 
You are provided with an array of integers called `target` with `n` elements. You start with another array, `arr`, consisting of `n` elements, all initialized to `1`. You have the ability to perform the following operation:

1. Calculate the sum of all elements in your current array `arr`, let's call it `x`.
2. Choose an index `i` where `0 <= i < n`, and update the value at index `i` in `arr` to be `x`.

You can repeat this operation as many times as needed. Your task is to determine whether it's possible to transform the initial array `arr` into the given `target` array using this operation. If it's possible, return `true`; otherwise, return `false`.

### Example 1
```text
Input: target = [9,3,5]
Output: true
Explanation: Start with arr = [1, 1, 1] 
[1, 1, 1], sum = 3 choose index 1
[1, 3, 1], sum = 5 choose index 2
[1, 3, 5], sum = 9 choose index 0
[9, 3, 5] Done
```

### Example 2
```text
Input: target = [1,1,1,2]
Output: false
Explanation: Impossible to create target array from [1,1,1,1].
```

### Example 3
```text
Input: target = [8,5]
Output: true
``` 

### Constraints

* `n == target.length`.
* `1 <= n <= 5 * 10^4`.
* `1 <= target[i] <= 10^9`.

## Solution 1: Going backward

If you start from `arr = [1,1,...,1]` and follow the required procedure, the new element `x` you get for the next state is always the max element of `arr`. 

To solve this problem, you can start from the max element of the given `target` to compute its previous state until you get the `arr = [1,1,...,1]`.

### Example 1
For `target = [9,3,5]`:

* The max element is `9`, subtract it from the remaining sum: `9 - (3 + 5) = 1`, you get `target = [1,3,5]`.
* The max element is `5`, subtract it from the remaining sum: `5 - (1 + 3) = 1`, you get `target = [1,3,1]`.
* The max element is `3`, subtract it from the remaining sum: `3 - (1 + 1) = 1`, you get `target = [1,1,1]`.
* Return `true`.

### Notes
* If `target = [m,1]` or `target = [1,m]` for any `m >= 1`, you can always turn it to `arr = [1,1]`.
* If the changed value after the subtraction is still the max element of the previous state, you need to redo the subtraction at the same position. In this case, the modulo might be used instead of subtraction.

### Code
```cpp
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;
bool isPossible(vector<int>& target) {
    unsigned long sum = accumulate(target.begin(), 
                                   target.end(), 
                                   (unsigned long) 0);
    auto pmax = max_element(target.begin(), target.end());
    while (*pmax > 1) {
        sum -= *pmax;
        if (sum == 1) {
            // This is the case target = [m,1], 
            // which you can always turn it to [1,1].
            return true;
        }
        if (*pmax <= sum) {
            return false;
        }
        if (sum == 0) {
            return false;
        }
        *pmax %= sum;
        if (*pmax == 0) {
            return false;
        }
        sum += *pmax;
        pmax = max_element(target.begin(), target.end());
    }
    return sum == target.size();
}
int main() {
    vector<int> target{9,3,5};
    cout << isPossible(target) << endl;
    target = {1,1,1,2};
    cout << isPossible(target) << endl;
    target = {8,5};
    cout << isPossible(target) << endl;
}
```
```text
Output:
1
0
1
```

### Code explanation

1. Calculate the sum of all elements in the `target` array using the `accumulate` function and store it in the variable `sum`. This sum represents the total value of the elements in the array.

2. Find the maximum element in the `target` array and store its iterator in the variable `pmax`.

3. Enter a loop that continues until the maximum element in the array becomes 1. The loop's purpose is to reduce the maximum element to 1 or determine if it's impossible to do so.

4. In each iteration of the loop:
   - Subtract the value of `*pmax` from `sum`. This simulates the operation of reducing the maximum element.
   - Check if `sum` has become 1. If it has, return `true` because you can always turn the array `[m,1]` into `[1,1]` by reducing `m` to 1.
   - Check if the maximum element `*pmax` is less than or equal to `sum`. If this condition is met, return `false` because you cannot reduce `*pmax` further without going below 1.
   - Check if `sum` has become 0. If it has, return `false` because you cannot reach an array of all 1s when the sum is zero.
   - Modify the maximum element `*pmax` by taking its modulus with `sum`. This reduces `*pmax` to a value smaller than the current maximum, allowing you to continue the process.
   - Add the modified `*pmax` back to `sum` to reflect the new total value of the array.

5. Update the maximum element `pmax` to point to the new maximum element in the modified `target` array.

6. After the loop ends, check if `sum` is equal to the size of the `target` array. If it is, return `true` because all elements in the array are now 1.

7. If none of the previous conditions are met, return `false` to indicate that it's impossible to obtain an array of all 1s.

In summary, this solution iteratively reduces the maximum element in the `target` array while keeping track of the total sum. It checks various conditions to determine whether it's possible to reach an array consisting of only 1s. If all conditions are satisfied, it returns `true`; otherwise, it returns `false`.

### Complexity
* Runtime: `O(log N)`, where `N = max(target)`.
* Extra space: `O(1)`.

## Solution 2: Using priority_queue

In the solution above, the position of the max element in each state is not so important as long as you update exactly it, not the other ones.

That might lead to the usage of the {index}`std::priority_queue`.

### Code
```cpp
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;
bool isPossible(vector<int>& target) {
    priority_queue<int> q(target.begin(), target.end());
    unsigned long sum = accumulate(target.begin(), target.end(), (unsigned long) 0);
    while (q.top() > 1) {
        sum -= q.top();
        if (sum == 1) {
            return true;
        }
        if (q.top() <= sum) {
            return false;
        }
        if (sum == 0) {
            return false;
        }
        int pre = q.top() % sum;
        if (pre == 0) {
            return false;
        }
        q.pop();
        q.push(pre);
        sum += pre;
    }
    return sum == target.size();
}
int main() {
    vector<int> target{9,3,5};
    cout << isPossible(target) << endl;
    target = {1,1,1,2};
    cout << isPossible(target) << endl;
    target = {8,5};
    cout << isPossible(target) << endl;
}
```
```text
Output:
1
0
1
```

### Code explanation

1. Initialize a max heap (priority queue) `q` with the elements from the `target` array. The max heap is used to efficiently find and process the maximum element.

2. Calculate the sum of all elements in the `target` array using the `accumulate` function and store it in the variable `sum`. This sum represents the total value of the elements in the array.

3. Enter a loop that continues until the maximum element in the `q` heap becomes 1. The loop's purpose is to reduce the maximum element to 1 or determine if it's impossible to do so.

4. In each iteration of the loop:
   - Subtract the value of `q.top()` (the maximum element in the heap) from `sum`. This simulates the operation of reducing the maximum element.
   - Check if `sum` has become 1. If it has, return `true` because you can always turn the array `[m,1]` into `[1,1]` by reducing `m` to 1.
   - Check if `q.top()` is less than or equal to `sum`. If this condition is met, return `false` because you cannot reduce `q.top()` further without going below 1.
   - Check if `sum` has become 0. If it has, return `false` because you cannot reach an array of all 1s when the sum is zero.
   - Calculate the remainder `pre` when `q.top()` is divided by `sum`. This represents the amount left after subtracting `q.top()` from `sum`.
   - Pop the maximum element `q.top()` from the heap.
   - Push the value `pre` back into the heap, as it represents the updated value of the maximum element.
   - Add `pre` to `sum` to reflect the new total value of the array.

5. After the loop ends, check if `sum` is equal to the size of the `target` array. If it is, return `true` because all elements in the array are now 1.

6. If none of the previous conditions are met, return `false` to indicate that it's impossible to obtain an array of all 1s.

### Complexity

This solution uses a max heap (`priority_queue`) to efficiently find and process the maximum element in the `target` array while keeping track of the total sum. It checks various conditions to determine whether it's possible to reach an array consisting of only 1s. If all conditions are satisfied, it returns `true`; otherwise, it returns `false`.

* Runtime: `O(logN)`, where `N = max(target)`.
* Extra space: `O(n)`, where `n = target.length`.


