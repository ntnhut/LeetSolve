# 448. Find All Numbers Disappeared in an Array

## Problem statement
Given an array `nums` of `n` integers where `nums[i]` is in the range `[1, n]`, return an array of all the integers in the range `[1, n]` that do not appear in `nums`.

### Example 1
```plain
Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
```

### Example 2
```plain
Input: nums = [1,1]
Output: [2]
```

### Constraints
* `n == nums.length`.
* `1 <= n <= 10^5`.
* `1 <= nums[i] <= n`.
 

### Follow up
Could you do it without extra space and in `O(n)` runtime? You may assume the returned list does not count as extra space.

## Solution: Marking the appearances

```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> findDisappearedNumbers(vector<int>& nums) {        
    vector<bool> exist(nums.size() + 1, false);        
    for (auto& i : nums) {
        exist[i] = true;
    }
    vector<int> result;
    for (int i = 1; i <= nums.size(); i++) {
        if (!exist[i]) {
            result.push_back(i);
        }
    }
    return result;
}
void print(vector<int>& nums) {
    cout << "[";
    for (auto& n : nums) {
        cout << n << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    auto result = findDisappearedNumbers(nums);
    print(result);
    nums = {1,1};
    result = findDisappearedNumbers(nums);
    print(result);
}
```
```plain
Output:
[5,6,]
[2,]
```

### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(1)` ([`vector<bool>`](https://en.cppreference.com/w/cpp/container/vector_bool) is optimized for space efficiency).

## References
* [https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)