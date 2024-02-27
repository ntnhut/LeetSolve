# Find the Duplicate Number
% Medium

## Problem statement

[^url]You have an array of integers called `nums` that contains `n + 1` integers. Each integer in the array falls within the range `[1, n]` inclusive.

Within this array, there is only one number that appears more than once. Your task is to find and return this repeated number.

Importantly, you must solve this problem without making any modifications to the original array `nums`, and you are only allowed to use a constant amount of extra space. 

[^url]: https://leetcode.com/problems/find-the-duplicate-number/
### Example 1
```text
Input: nums = [1,3,4,2,2]
Output: 2
```

### Example 2
```text
Input: nums = [3,1,3,4,2]
Output: 3
``` 

### Constraints

* `1 <= n <= 10^5`.
* `nums.length == n + 1`.
* `1 <= nums[i] <= n`.
* All the integers in `nums` appear only once except for precisely one integer which appears two or more times.
 

### Follow up

* How can we prove that at least one duplicate number must exist in `nums`?
* Can you solve the problem in linear runtime complexity?


## Solution 1: {index}`Sorting`

### Code

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int findDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 1; i++) {
        if (nums[i] == nums[i + 1]) {
            return nums[i];
        }
    }
    return 0;
}
int main() {
    vector<int> nums{1,3,4,2,2};
    cout << findDuplicate(nums) << endl;
    nums = {3,1,3,4,2};
    cout << findDuplicate(nums) << endl;
}
```
```text
Output:
2
3
```

The code relies on sorting to bring duplicate elements together, making it easy to identify them during the linear pass.

### Complexity

* Runtime: `O(n*logn)` (sorting).
* Extra space: `O(1)`.

## Follow up

### How can we prove that at least one duplicate number must exist in `nums`?

Due to [Pigeonhole principle](https://en.wikipedia.org/wiki/Pigeonhole_principle):

Here there are `n + 1` pigeons in `n` holes. The pigeonhole principle says that at least one hole has more than one pigeon.

### Can you solve the problem in linear runtime complexity?
Here are a few solutions.

## Solution 2: Marking the visited numbers

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int findDuplicate(const vector<int>& nums) {
    // initialize n + 1 elements false
    vector<bool> visited(nums.size());
    for (auto& a : nums) {        
        if (visited.at(a)) {
            return a;
        }
        visited[a] = true;
    }
    return 0;
}
int main() {
    vector<int> nums{1,3,4,2,2};
    cout << findDuplicate(nums) << endl;
    nums = {3,1,3,4,2};
    cout << findDuplicate(nums) << endl;
}
```
```text
Output:
2
3
```

This solution utilizes a boolean array `visited` to track visited elements. 

It iterates through the elements of the input vector `nums`, marking each element as visited by setting the corresponding index in the `visited` array to true. Upon encountering a visited element, it immediately returns it as the duplicate element. 

This approach efficiently identifies the duplicate element in the vector by tracking visited elements without requiring additional space proportional to the size of the input vector.

### Complexity
* Runtime: `O(n)`.
* Extra space: much less than `O(n)`. [`std::vector<bool>`](https://en.cppreference.com/w/cpp/container/vector_bool) is optimized for space-efficient. 

## Solution 3: Marking with {index}`std::bitset`

Since `n <= 10^5`, you can use this size for a [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset) to do the marking. 

### Code
```cpp
#include <vector>
#include <iostream>
#include <bitset>
using namespace std;
int findDuplicate(const vector<int>& nums) {
    // initialize visited = '000..0' with 100001 bits 0
    bitset<100001> visited;
    for (auto& a : nums) {
        if (visited[a]) {
            return a;
        }
        // set a-th bit to 1
        visited[a] = 1;
    }
    return 0;
}
int main() {
    vector<int> nums{1,3,4,2,2};
    cout << findDuplicate(nums) << endl;
    nums = {3,1,3,4,2};
    cout << findDuplicate(nums) << endl;
}
```
```text
Output:
2
3
```

This code uses a bitset to keep track of visited elements and quickly detects any duplicate element encountered during the iteration.

### Complexity

* Runtime: `O(n)`.
* Extra space: `O(1)`. 

## Key Takeaway

Different strategies can be employed to detect duplicates in an array, such as sorting followed by linear search, using a hash set to track visited elements, or utilizing a bitset to mark visited indices. 

Each approach has its trade-offs in terms of time complexity, space complexity, and implementation simplicity. To me, Solution 2 balances all the trade-offs. What do you think?

## Exercise
- [Missing Number](https://leetcode.com/problems/missing-number/)