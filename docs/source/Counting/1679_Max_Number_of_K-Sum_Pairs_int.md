# Max Number of K-Sum Pairs
% Medium
## Problem statement

[^url]You're provided with an array of integers called `nums` and an integer `k`. Each operation involves selecting two numbers from the array whose sum is equal to `k`, and then removing them from the array. Your goal is to determine the maximum count of such operations you can perform on the array. 

[^url]: https://leetcode.com/problems/max-number-of-k-sum-pairs/
### Example 1
```text
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
```

### Example 2
```text
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
``` 

### Constraints

* `1 <= nums.length <= 10^5`.
* `1 <= nums[i] <= 10^9`.
* `1 <= k <= 10^9`.

## Solution: Count the appearances

You can use a map to count the appearances of the elements of `nums`.

### Example 2
For `nums = [3,1,3,4,3]` and `k = 6`:

* Initialize `count = 0`.
* For `i = 0`: `m[3] = 1`; `k - 3 = 3` but `m[3]` is only `1`, not enough to have two numbers.
* For `i = 1`: `m[1] = 1`; `k - 1 = 5` and `m[5] = 0`.
* For `i = 2`: `m[3] = 2`; `k - 3 = 3` and `m[3] = 2` just enough to have two numbers to perform the sum. `count = 1`. Erase those two values `3`'s from the map: `m[3] = 0`.
* For `i = 3`: `m[4] = 1`; `k - 4 = 2` and `m[2] = 0`.
* For `i = 4`: `m[3] = 1`; `k - 3 = 3` but `m[3]` is only `1`, not enough to have two numbers.
* Final `count = 1`.

### Code
```cpp
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
int maxOperations(vector<int>& nums, int k) {
    unordered_map<int,int> m;
    int count = 0;
    for (int a : nums) {
        m[a]++;
        if (m[k - a] > 0) {
            if (a != k - a || m[a] >= 2) {
                count++;
                m[a]--;
                m[k - a]--;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,2,3,4};
    cout << maxOperations(nums, 5) << endl;
    nums = {3,1,3,4,3};
    cout << maxOperations(nums, 6) << endl;
}
```
```text
Output:
2
1
```

This solution efficiently counts the number of pairs in the given array `nums` whose sum equals the target value `k`. It utilizes an unordered map to store the frequency of each element encountered while iterating through `nums`. 

By examining each element `a` in `nums`, it checks if `k - a` exists in the map and if its frequency is greater than 0. If so, it increments the count of pairs and decrements the frequency of both `a` and `k - a`, ensuring that each pair is counted only once. 

This approach optimizes the computation by efficiently tracking the frequencies of elements and identifying valid pairs whose sum equals the target value without requiring additional space proportional to the size of the array.

### Complexity

* Runtime: `O(n)`, where `n` is the number of elements in the `nums` array.
* Extra space: `O(n)`.

## Exercise
- [Two Sum](https://leetcode.com/problems/two-sum/)