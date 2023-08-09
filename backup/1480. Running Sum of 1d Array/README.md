# 1480. Running Sum of 1d Array

## Problem statement

Given an array `nums`. We define a running sum of an array as `runningSum[i] = sum(nums[0]…nums[i])`.

Return the running sum of `nums`.

### Example 1
```plain
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
```

### Example 2
```plain
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
```

### Example 3
```plain
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
``` 

### Constraints

* `1 <= nums.length <= 1000`.
* `-10^6 <= nums[i] <= 10^6`.

## Solution 1: Unchange `nums`

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> runningSum(vector<int>& nums) {
    vector<int> rs;
    int s = 0;
    for (int n : nums) {
        s += n;
        rs.push_back(s);
    }
    return rs;
}
void printResult(vector<int>& sums) {
    cout << "[";
    for (int s: sums) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,2,3,4};
    auto rs = runningSum(nums);
    printResult(rs);
    nums = {1,1,1,1,1};
    rs = runningSum(nums);
    printResult(rs);
    nums = {3,1,2,10,1};
    rs = runningSum(nums);
    printResult(rs);
}
```
```plain
Output:
[1,3,6,10,]
[1,2,3,4,5,]
[3,4,6,16,17,]
```

### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(1)`.

## Solution 2: Change `nums`

If `nums` is allowed to be changed, you could use it to store the result directly.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> runningSum(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        nums[i] += nums[i - 1];
    }
    return nums;
}
void printResult(vector<int>& sums) {
    cout << "[";
    for (int s: sums) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,2,3,4};
    auto rs = runningSum(nums);
    printResult(rs);
    nums = {1,1,1,1,1};
    rs = runningSum(nums);
    printResult(rs);
    nums = {3,1,2,10,1};
    rs = runningSum(nums);
    printResult(rs);
}
```
```plain
Output:
[1,3,6,10,]
[1,2,3,4,5,]
[3,4,6,16,17,]
```

### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(1)`.


## References
* [https://leetcode.com/problems/running-sum-of-1d-array/](https://leetcode.com/problems/running-sum-of-1d-array/)
* [https://www.leetsolve.com/1480-running-sum-of-1d-array/](https://www.leetsolve.com/1480-running-sum-of-1d-array/)