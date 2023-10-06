# Find the Duplicate Number


## [Problem statement](https://leetcode.com/problems/find-the-duplicate-number/)

You have an array of integers called `nums` that contains `n + 1` integers. Each integer in the array falls within the range `[1, n]` inclusive.

Within this array, there is only one number that appears more than once. Your task is to find and return this repeated number.

Importantly, you must solve this problem without making any modifications to the original array `nums`, and you are only allowed to use a constant amount of extra space. 

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
 

**Follow up**:

* How can we prove that at least one duplicate number must exist in `nums`?
* Can you solve the problem in linear runtime complexity?


## Solution 1: Sorting

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

### Code explanation

1. The code sorts the `nums` vector in ascending order.

2. It iterates through the sorted vector, comparing each element with the one next to it.

3. If it finds two adjacent elements that are equal, it returns that element as it is the duplicate.

4. If no duplicate is found during the loop, it returns 0 as a default value.


### Complexity
The code relies on sorting to bring duplicate elements together, making it easy to identify them during the linear pass. The time complexity is `O(n*logn)` due to the sorting operation.

* Runtime: `O(n*logn)`.
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
int findDuplicate(vector<int>& nums) {
    vector<bool> visited(nums.size());
    for (int a : nums) {
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

### Code explanation

1. The code creates a Boolean vector `visited` with the same size as the `nums` vector to keep track of visited elements.

2. For each element `a` in the `nums` vector, it checks if the corresponding index in the `visited` vector is already marked as `true`. If it is, it returns `a` as it is the duplicate.

3. If the element is not marked as visited, it sets the corresponding index in the `visited` vector to `true` to mark it as visited.

4. If no duplicates are found during the loop, it returns 0 as a default value.

### Complexity
* Runtime: `O(n)`.
* Extra space: much less than `O(n)`. [`std::vector<bool>`](https://en.cppreference.com/w/cpp/container/vector_bool) is optimized for space-efficient. 

## Solution 3: Marking with `std::bitset`

Since `n <= 10^5`, you can use this size for a [`std::bitset`](https://en.cppreference.com/w/cpp/utility/bitset) to do the marking. 

### Code
```cpp
#include <vector>
#include <iostream>
#include <bitset>
using namespace std;
int findDuplicate(vector<int>& nums) {
    bitset<100001> visited;
    for (int a : nums) {
        if (visited[a]) {
            return a;
        }
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

### Code explanation

1. The code creates a `bitset` named `visited` with a size of 100001, which is large enough to accommodate the possible values in the `nums` vector.

2. For each element `a` in `nums`, it checks if the corresponding bit in the `visited` `bitset` is set (1). If it is, the code returns `a` as it is the duplicate.

3. If the bit is not set, the code sets the corresponding bit in the `visited` `bitset` to 1 to mark it as visited.

4. If no duplicates are found during the loop, it returns 0 as a default value.

### Complexity
This code efficiently uses a bitset to keep track of visited elements and quickly detects any duplicate element encountered during the iteration. The time complexity is `O(n)` because it makes a single pass through the input vector.

* Runtime: `O(n)`.
* Extra space: `O(1)`. 
