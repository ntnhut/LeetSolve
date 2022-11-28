# 565. Array Nesting
Tags: medium

## Problem statement
You are given an integer array `nums` of length `n` where `nums` is a permutation of the numbers in the range `[0, n - 1]`.

You should build a set `s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... }` subjected to the following rule:

* The first element in `s[k]` starts with the selection of the element `nums[k]` of `index = k`.
* The next element in `s[k]` should be `nums[nums[k]]`, and then `nums[nums[nums[k]]]`, and so on.
* We stop adding right before a duplicate element occurs in `s[k]`.

Return the longest length of a set `s[k]`. 

### Example 1
```plain
Input: nums = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
One of the longest sets s[k]:
s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
```

### Example 2
```plain
Input: nums = [0,1,2]
Output: 1
``` 

### Constraints:

* `1 <= nums.length <= 10^5`.
* `0 <= nums[i] < nums.length`.
* All the values of `nums` are unique.

## Solution: Understanding the math behind
A [permutation](https://en.wikipedia.org/wiki/Permutation) is a one-to-one mapping from a set of integers to itself.

The permutation `nums` in this problem is defined as `i -> nums[i]`. For instance in Example 1, the permutation is defined as following:
```plain
0 -> 5,
1 -> 4,
2 -> 0,
3 -> 3,
4 -> 1,
5 -> 6,
6 -> 2.
```
You can always rearrange the definition of a permutation into groups of cyclic chains (factors). 
```plain
0 -> 5, 5 -> 6, 6 -> 2, 2 -> 0,
1 -> 4, 4 -> 1,
3 -> 3
```
The set `s[k]` in this problem is such a chain. In mathematics, it is called a *cycle*.

The problem leads to finding the longest cycle of a given permutation.

### Code
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int arrayNesting(vector<int>& nums) {
    int maxLen(0);
    vector<bool> visited(nums.size());
    for (auto i : nums) {
        if (visited[i]) {
            continue;
        }
        int len(0);
        while (!visited[i]) {
            visited[i] = true;
            i = nums[i];            
            len++;
        }
        maxLen = max(len, maxLen);
    }
    return maxLen;
}

int main() {
    vector<int> nums = {5,4,0,3,1,6,2}; 
    cout << arrayNesting(nums) << endl;
    nums = {0,1,2}; 
    cout << arrayNesting(nums) << endl;
    nums = {0,2,1}; 
    cout << arrayNesting(nums) << endl;
    nums = {2,0,1}; 
    cout << arrayNesting(nums) << endl;
}
```
```plain
Output:
4
1
2
3
```

### Complexity
* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(logN)`.

## Implementation note
In the code above we can skip visited elements because in a permutation distinct cycles are disjoint.

## References
* [https://leetcode.com/problems/array-nesting/](https://leetcode.com/problems/array-nesting/)
* [https://www.leetsolve.com/565-array-nesting](https://www.leetsolve.com/565-array-nesting)