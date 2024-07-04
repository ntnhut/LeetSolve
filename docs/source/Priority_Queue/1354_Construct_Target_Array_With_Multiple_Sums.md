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
bool isPossible(const vector<int>& target) {
    // compute sum of all target's elements
    unsigned long sum = accumulate(target.begin(), 
                                   target.end(), 
                                   (unsigned long) 0);
    // find the max element in the target
    // pmax is the pointer to the max element,
    // *pmax is the value that pointer points to
    auto pmax = max_element(target.begin(), target.end());
    while (*pmax > 1) {
        // compute the remaining sum
        sum -= *pmax;
        if (sum == 1) {
            // This is the case target = [m,1], 
            // which you can always turn it to [1,1].
            return true;
        }        
        if (*pmax <= sum) {
            // the next subtraction leads to non-positive values
            return false;
        }
        if (sum == 0) {
            // cannot change target
            return false;
        }
        // perform the subtraction as much as possible
        // and update new value for the pointer pmax
        *pmax %= sum;
        if (*pmax == 0) {
            return false;
        }
        // compute the sum of the subtracted target
        sum += *pmax;
        // find the max element in the subtracted target
        pmax = max_element(target.begin(), target.end());
    }
    // if the final target = [1, .., 1],
    // its sum equals to its length
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

This solution iteratively reduces the maximum element in the `target` array while keeping track of the total sum. It checks various conditions to determine whether it's possible to reach an array consisting of only 1s. If all conditions are satisfied, it returns `true`; otherwise, it returns `false`.

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
bool isPossible(const vector<int>& target) {
    // create a heap from the target
    priority_queue<int> q(target.begin(), target.end());
    // compute the sum of all elements
    unsigned long sum = accumulate(target.begin(), 
                                   target.end(), 
                                   (unsigned long) 0);
    while (q.top() > 1) {
        // compute the remaining sum
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
        // perform the subtraction as much as possible
        int pre = q.top() % sum;
        if (pre == 0) {
            return false;
        }
        // remove the old max element
        q.pop();
        // add subtracted element to the heap
        q.push(pre);
        // compute the sum of the subtracted target
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

### Complexity

* Runtime: `O(logN)`, where `N = max(target)`.
* Extra space: `O(n)`, where `n = target.length`.

## Conclusion

Solution 2 uses a max heap (`priority_queue`) to efficiently find and process the maximum element in the `target` array while keeping track of the total sum. It checks various conditions to determine whether it's possible to reach an array consisting of only 1s. 

## Exercise
- [Minimum Amount of Time to Fill Cups](https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/).


