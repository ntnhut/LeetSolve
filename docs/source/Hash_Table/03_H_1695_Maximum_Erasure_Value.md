# Maximum Erasure Value

## [Problem statement](https://leetcode.com/problems/maximum-erasure-value/)

You have an array of positive integers called `nums`, and you wish to remove a subarray from it that consists of distinct elements. The score you achieve by removing this subarray is the sum of its elements.

Your goal is to determine the highest possible score attainable by erasing exactly one subarray from the provided array.

A subarray, denoted as `b`, is considered part of another array, `a`, if it appears consecutively within `a`, i.e., if it is equivalent to `a[l], a[l+1], ..., a[r]` for some indices `(l, r)`.

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
```

### Code explanation

This C++ code defines a function called `maximumUniqueSubarray` that finds the maximum sum of a subarray in the given vector `nums` with the constraint that all elements in the subarray must be unique. It uses two key techniques: prefix sums and a sliding window approach.

Here's a step-by-step explanation of how the code works:

1. The code initializes a vector called `sum` of the same size as the input `nums`. `sum` is used to store the cumulative sums of elements in `nums`, where `sum[i]` represents the sum of the first `i` elements of `nums`. The initial value of `sum[0]` is set to `nums[0]`.

2. It initializes the `maxSum` variable to the value of `sum[0]`, which represents the maximum sum found so far.

3. An unordered map called `position` is created to store the position (index) of each element in `nums`. This map is used to keep track of the most recent position where each element was encountered.

4. The initial position of the first element, `nums[0]`, is set to `0` in the `position` map.

5. The `start` variable is initialized to `-1`, which will be used to keep track of the starting index of the subarray with unique elements.

6. The code enters a loop that iterates for each element in `nums` except the first one.

7. The `sum` vector is updated with the cumulative sum up to the current element `nums[i]`. This is done to efficiently calculate the sum of any subarray later.

8. Inside the loop, the code checks if the current element `nums[i]` is already in the `position` map. If `nums[i]` is found in the `position` map, it means that this element has been encountered before. In this case, the code updates the `start` variable to be the maximum of its current value and the position of `nums[i]` from the `position` map. This is the sliding window technique to ensure that the subarray only contains unique elements.

9. The current position of `nums[i]` is updated in the `position` map.

10. The code calculates the maximum sum using the sliding window approach. If `start` is still equal to `-1`, it means that all elements up to `nums[i]` are unique, so the maximum sum is simply `sum[i]`. Otherwise, the code calculates the maximum of the current `maxSum` and the sum of the elements between the current position `i` and the `start` position. This ensures that the subarray contains unique elements.

11. Finally, the function returns `maxSum`, which contains the maximum sum of a subarray with unique elements.

In summary, this code efficiently finds the maximum sum of a subarray with unique elements using a sliding window approach and prefix sums. 

### Complexity
* Runtime: $O(N)$, where $N$ is `nums.length`.
* Extra space: $O(N)$.


