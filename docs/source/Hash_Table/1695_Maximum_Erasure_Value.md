# Maximum Erasure Value
% Medium
## Problem statement

[^url]You have an array of positive integers called `nums`, and you wish to remove a subarray from it that consists of distinct elements. The score you achieve by removing this subarray is the sum of its elements.

Your goal is to determine the highest possible score attainable by erasing exactly one subarray from the provided array.

A subarray, denoted as `b`, is considered part of another array, `a`, if it appears consecutively within `a`, i.e., if it is equivalent to `a[l], a[l+1], ..., a[r]` for some indices `(l, r)`.

[^url]: https://leetcode.com/problems/maximum-erasure-value/ 
### Example 1
```text
Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
```

### Example 2
```text
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
    sum[0] = nums.at(0);
    int maxSum = sum.at(0);
    unordered_map<int, int> position;
    position[nums.at(0)] = 0;
    int start = -1;
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum.at(i - 1) + nums.at(i);
        auto it = position.find(nums.at(i));
        if (it != position.end()) {
            start = max(start, it->second);
            it->second = i;
        } else {
            position.insert({nums.at(i), i});
        }            
        if (start == -1) {
            maxSum = sum.at(i);
        } else {
            maxSum = max(maxSum, sum.at(i) - sum.at(start));
        }
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
```text
Output:
17
8
```

### Code explanation

This solution computes the maximum sum of a subarray containing unique elements. 

It uses a {index}`sliding window` approach to maintain a running sum of the elements encountered so far and a hashmap to keep track of the positions of previously seen elements. By updating the starting index of the window when a repeated element is encountered, it ensures that the current subarray contains only unique elements. 

This approach optimizes the computation of the maximum sum by handling the sliding window and updating the sum accordingly, resulting in an overall efficient solution.

### Complexity

* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(N)`.


