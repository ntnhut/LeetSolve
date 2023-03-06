## 560. Subarray Sum Equals K
Tag: medium

### Problem Statement
Given an array of integers `nums` and an integer `k`, return the total number of continuous subarrays whose sum equals to `k`.

#### Example 1
```plain
Input: nums = [1,1,1], k = 2
Output: 2
```
#### Example 2
```plain
Input: nums = [1,2,3], k = 3
Output: 2
``` 

#### Constraints

* `1 <= nums.length <= 2 * 10^4`.
* `-1000 <= nums[i] <= 1000`.
* `-10^7 <= k <= 10^7`.

### Solution 1: Bruteforce

For each element, for all subarrays starting from it, choose the satisfied ones.

#### Example 3
For `nums = [1, -1, 0]` and `k = 0`, you get `3` subarrays for the result:
* There are three subarrays starting from `1`, which are `[1]`, `[1, -1]`, and `[1, -1, 0]`. Only the last two are satisfied.
* There are two subarrays starting from `-1`, which are `[-1]` and `[-1, 0]`. None is satisfied.
* Only `[0]` is the subarray starting from `0`. It is satisfied.

#### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
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
```plain
Output:
2
2
3
```
#### Complexity
* Runtime: `O(N^2)`, where `N = nums.length`.
* Extra space: `O(1)`.

### Solution 2: Prefix sum
In the solution above, many sums can be deducted from the previous ones.

#### Example 4
For `nums = [1, 2, 3, 4]`. Assume the sum of the subarrays `[1], [1, 2], [1, 2, 3], [1, 2, 3, 4]` were computed in the first loop. Then the sum of any other subarray can be deducted from those values.
* `sum([2, 3]) = sum([1, 2, 3]) - sum([1])`.
* `sum([2, 3, 4]) = sum([1, 2, 3, 4]) - sum([1])`.
* `sum([3, 4]) = sum(1, 2, 3, 4) - sum(1, 2)`.

In general, assume you have computed the sum `sum[i]` for the subarray `[nums[0], nums[1], ..., nums[i]]` for all `0 <= i < nums.length`. Then the sum of the subarray `[nums[j], nums[j+1], ..., nums[i]]` for any `0 <=j <= i` can be computed as `sum[i] - sum[j]`.

#### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
    vector<int> sum(nums.size());
    sum[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i-1] + nums[i];
    }
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (sum[i] == k) {
            count++;
        }
        for (int j = 0; j < i; j++) {
            if (sum[i] - sum[j] == k) {
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
```plain
Output:
2
2
3
```
#### Complexity
* Runtime: `O(N^2)`, where `N = nums.length`.
* Extra space: `O(N)`.

### Solution 3: Faster lookup

You can rewrite the condition `sum[i] - sum[j] == k` in the inner loop of the Solution 2 to `sum[i] - k == sum[j]`. 

Then that loop can rephrase to *"checking if `sum[i] - k` was already a value of **some** computed `sum[j]`"*. 

Now you can use an `unordered_map` to store the `sums` as indices for the fast lookup.

#### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    unordered_map<int, int> sums;
    int sumi = 0;
    for (int i = 0; i < nums.size(); i++) {
        sumi += nums[i];
        if (sumi == k) {
            count++;
        }
        auto it = sums.find(sumi - k);
        if (it != sums.end()) {
            count += it->second;
        }
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
```plain
Output:
2
2
3
```
#### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(N)`.

## References
* [https://leetcode.com/problems/subarray-sum-equals-k/](https://leetcode.com/problems/subarray-sum-equals-k/)