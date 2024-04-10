# Maximum Subarray
% Medium 
## Problem statement

[^url]You're provided with an array of integers called `nums`. Your task is to identify a subarray (a consecutive sequence of numbers) that has the highest sum. Once you find this subarray, return the sum of its elements.

[^url]: https://leetcode.com/problems/maximum-subarray/

### Example 1
```text
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

### Example 2
```text
Input: nums = [1]
Output: 1
```

### Example 3
```text
Input: nums = [5,4,-1,7,8]
Output: 23
```

### Constraints

* `1 <= nums.length <= 10^5`.
* `-10^4 <= nums[i] <= 10^4`.
 
## Solution

The subarrays you want to find should not have negative prefix sums. A negative prefix sum would make the sum of the subarray smaller.

### Example 1
For `nums = [-2,1,-3,4,-1,2,1,-5,4]`, `[-2]` or `[-2,1]` or `[-2,1,-3]` should not be a prefix of the subarrays you want to find. Since it makes the sum of the result smaller.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxSubArray(const vector<int>& nums) {
    int maxSum = -10000; // just chose some negative number to start
    int currSum = 0; // sum of current subarray
    for (auto& num : nums) {
        if (currSum < 0) {
            // start a new subarray from this num
            currSum = num;
        } else {
            currSum = currSum + num;
        }
        // update max sum so far
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}
int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl;
    nums = {1};
    cout << maxSubArray(nums) << endl;
    nums = {5,4,-1,7,8};
    cout << maxSubArray(nums) << endl;
}
```
```text
Output:
6
1
23
```

### Complexity
* Runtime `O(n)`, where `n = nums.length`.
* Memory `O(1)`.

## Conclusion

This solution is the {index}`Kadane's algorithm`[^kad] to find the maximum sum of a contiguous subarray in the given array nums. 

[^kad]: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm

It iterates through the elements of the array, updating `currSum` to either the current element or the sum of the current element and the previous `currSum`, whichever is greater. By considering whether adding the current element improves the overall sum, it effectively handles both positive and negative numbers in the array. Finally, it updates `maxSum` with the maximum value encountered during the iteration, ensuring it holds the maximum sum of any contiguous subarray within the given array. 

This approach optimizes the computation by tracking the maximum sum and dynamically updating it as it iterates through the array.

## Exercise
- Maximum Product Subarray[^ex].

[^ex]: https://leetcode.com/problems/maximum-product-subarray/