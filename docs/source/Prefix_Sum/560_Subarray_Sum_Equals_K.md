# Subarray Sum Equals K
% Medium
## Problem Statement

[^url]You have an array of integers called `nums` and an integer `k`. Your task is to determine the count of contiguous subarrays within this array, where the sum of elements in each subarray is equal to the value of `k`.

[^url]: https://leetcode.com/problems/subarray-sum-equals-k/
### Example 1
```text
Input: nums = [1,1,1], k = 2
Output: 2
```
### Example 2
```text
Input: nums = [1,2,3], k = 3
Output: 2
``` 

### Constraints

* `1 <= nums.length <= 2 * 10^4`.
* `-1000 <= nums[i] <= 1000`.
* `-10^7 <= k <= 10^7`.

## Solution 1: Bruteforce

For each element, for all subarrays starting from it, choose the satisfied ones.

### Example 3
For `nums = [1, -1, 0]` and `k = 0`, you get `3` subarrays for the result:
* There are three subarrays starting from `1`, which are `[1]`, `[1, -1]`, and `[1, -1, 0]`. Only the last two are satisfied.
* There are two subarrays starting from `-1`, which are `[-1]` and `[-1, 0]`. None is satisfied.
* Only `[0]` is the subarray starting from `0`. It is satisfied.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(const vector<int>& nums, int k) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

This solution employs a brute-force approach by considering all possible subarrays and checking whether their sum equals the target `k`. The time complexity of this solution is relatively high due to the nested loops, resulting in an inefficient algorithm for larger input sizes.

### Complexity
* Runtime: `O(n^2)`, where `n = nums.length`.
* Extra space: `O(1)`.

## Solution 2: Prefix sum
In the solution above, many sums can be deducted from the previous ones.

### Example 4
For `nums = [1, 2, 3, 4]`. Assume the sum of the subarrays `[1], [1, 2], [1, 2, 3], [1, 2, 3, 4]` were computed in the first loop. Then the sum of any other subarray can be deducted from those values.
* `sum([2, 3]) = sum([1, 2, 3]) - sum([1])`.
* `sum([2, 3, 4]) = sum([1, 2, 3, 4]) - sum([1])`.
* `sum([3, 4]) = sum(1, 2, 3, 4) - sum(1, 2)`.

In general, assume you have computed the sum `sum[i]` for the subarray `[nums[0], nums[1], ..., nums[i]]` for all `0 <= i < nums.length`. Then the sum of the subarray `[nums[j+1], nums[j+2], ..., nums[i]]` for any `0 <= j <= i` can be computed as `sum[i] - sum[j]`.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(const vector<int>& nums, int k) {
    const int n = nums.size();
    vector<int> sum(n);
    sum[0] = nums[0];
    // compute all prefix sums nums[0] + .. + nums[i]
    for (int i = 1; i < n; i++) {
        sum[i] = sum[i-1] + nums[i];
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (sum[i] == k) {
            // nums[0] + .. + nums[i] = k
            count++;
        }
        for (int j = 0; j < i; j++) {
            if (sum[i] - sum[j] == k) {
                // nums[j+1] + nums[j+2] + .. + nums[i] = k
                count++;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

This solution uses the concept of prefix sum to efficiently calculate the sum of subarrays. It then iterates through the array to find subarrays with a sum equal to `k`, and the nested loop helps in calculating the sum of various subarray ranges. The time complexity of this solution is improved compared to the brute-force approach.

### Complexity
* Runtime: `O(n^2)`, where `n = nums.length`.
* Extra space: `O(n)`.

## Solution 3: Faster lookup

You can rewrite the condition `sum[i] - sum[j] == k` in the inner loop of the Solution 2 to `sum[i] - k == sum[j]`. 

Then that loop can rephrase to *"checking if `sum[i] - k` was already a value of **some** computed `sum[j]`"*. 

Now you can use an `unordered_map` to store the `sums` as indices for the fast lookup.

### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int subarraySum(const vector<int>& nums, int k) {
    int count = 0;
    // count the frequency of all subarrays' sums 
    unordered_map<int, int> sums;
    int sumi = 0;
    for (int i = 0; i < nums.size(); i++) {
        sumi += nums[i];
        if (sumi == k) {
            count++;
        }
        auto it = sums.find(sumi - k);
        if (it != sums.end()) {
            // it->second is the count of j so far 
            // having sum[j] = sum[i] - k
            count += it->second;
        }
        // store the count of prefix sum sumi
        sums[sumi]++;
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(n)`.

## Key Takeaway

Solution 3 uses an unordered map to efficiently track the frequency of cumulative sums. It utilizes the concept of complement sums to identify subarrays with the desired sum and adds their counts to the overall count. This approach significantly improves the time complexity compared to the brute-force solution.

## Exercise
- [Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)