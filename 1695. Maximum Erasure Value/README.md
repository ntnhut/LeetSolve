# 1695. Maximum Erasure Value

## Problem statement

You are given an array of positive integers `nums` and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.

An array `b` is called to be a subarray of `a` if it forms a contiguous subsequence of `a`, that is, if it is equal to `a[l],a[l+1],...,a[r]` for some `(l,r)`.

 

### Example 1
```plain
Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
```

### Example 2
```plain
Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
``` 

### Constraints

* `1 <= nums.length <= 10^5`.
* `1 <= nums[i] <= 10^4`.

## Solution: Store the position of the visited elements

You can use a map to store the position of the elements of `nums`. Then when iterating `nums` you can identify if an element has been visited before. That helps you to decide if a subarray contains unique elements.


### Code
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
int maximumUniqueSubarray(vector<int>& nums) {
    vector<int> sum(nums.size(), 0);
    sum[0] = nums[0];    
    int maxSum = sum[0];
    unordered_map<int, int> position;
    position[nums[0]] = 0;
    int start = -1;
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i - 1] + nums[i];
        if (position.find(nums[i]) != position.end()) {
            start = max(start, position[nums[i]]);
        }
        position[nums[i]] = i;
        maxSum = (start == -1) ? sum[i] : max(maxSum, sum[i] - sum[start]);
    }
    return maxSum;
}
int main() {
    vector<int> nums{4,2,4,5,6};
    cout << maximumUniqueSubarray(nums) << endl;
    nums = {5,2,1,2,5,2,1,2,5};
    cout << maximumUniqueSubarray(nums) << endl;
}
```
```plain
Output:
17
8
```

### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(N)`.

## References
* [https://leetcode.com/problems/maximum-erasure-value/](https://leetcode.com/problems/maximum-erasure-value/)
* [https://www.leetsolve.com/1695-maximum-erasure-value](https://www.leetsolve.com/1695-maximum-erasure-value)