# 462. Minimum Moves to Equal Array Elements II

## Problem Statement

Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by `1`.

### Example 1

```text
Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed:
[1,2,3] => [2,2,3] => [2,2,2]
```

### Example 2

```text
Input: nums = [1,10,2,9]
Output: 16
```

### Constraints

- `n == nums.length`
- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

---

## First Intuition

If the common destination is `M`, then each value contributes `|nums[i] - M|` moves. The total cost is therefore the sum of the absolute distances from all array elements to `M`.

We want a target that balances the values on either side. The median is a natural candidate: moving the target away from the median makes at least as many values farther away as closer. That is why the median minimizes the sum of absolute differences, while the mean does not necessarily do so.

The straightforward implementation sorts the values to find the median. But the calculation only needs the middle value, not the complete sorted order. That lets us replace sorting with a selection algorithm.

---

## Approach 1: Sort and Choose the Median

### Idea

Sort the array and choose `nums[n / 2]` as the target. For an even-sized array, this is the upper middle value; either middle value minimizes the total cost.

To see why a median works, imagine shifting the target one step to the right. Each value to its left becomes one step farther away, and each value to its right becomes one step closer. To the left of a median, at least as many values lie to the right as to the left, so shifting right cannot increase the total cost. To the right of a median, at least as many values lie to the left as to the right, so shifting farther right cannot reduce the cost. The same reasoning applies when shifting left.

For `[0,1,2,2,10]`, choosing the median `2` costs `2 + 1 + 0 + 0 + 8 = 11`. Choosing the mean, `3`, costs `3 + 2 + 1 + 1 + 7 = 14`.

### Code

```cpp
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

long long minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    const int median = nums[nums.size() / 2];
    long long moves = 0;
    for (int value : nums) {
        moves += llabs(static_cast<long long>(value) - median);
    }
    return moves;
}

int main() {
    vector<int> nums{1, 2, 3};
    cout << minMoves2(nums) << endl;
    nums = {1, 10, 2, 9};
    cout << minMoves2(nums) << endl;
}
```

```text
Output:
2
16
```

### Complexity

- **Time:** `O(n log n)` for sorting.
- **Space:** `O(1)` auxiliary space, excluding implementation-specific sorting storage.

### Limitations

The sort gives us more ordering information than the cost calculation needs. We only use the median, so fully sorting the array is unnecessary.

---

## Approach 2: Use `std::nth_element`

### Idea

The C++ algorithm `std::nth_element` rearranges the array so the element at the selected position is the same as it would be in a sorted array. Elements before it are no greater, and elements after it are no smaller, but neither side is fully sorted.

Selecting the element at `n / 2` gives us the median. We can then make the same pass over the array to sum the distances. The result is linear time on average instead of `O(n log n)`.

### Code

```cpp
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

long long minMoves2(vector<int>& nums) {
    const size_t mid = nums.size() / 2;
    nth_element(nums.begin(), nums.begin() + mid, nums.end());
    const int median = nums[mid];

    long long moves = 0;
    for (int value : nums) {
        moves += llabs(static_cast<long long>(value) - median);
    }
    return moves;
}

int main() {
    vector<int> nums{1, 2, 3};
    cout << minMoves2(nums) << endl;
    nums = {1, 10, 2, 9};
    cout << minMoves2(nums) << endl;
}
```

```text
Output:
2
16
```

### Complexity

- **Time:** `O(n)` on average for `nth_element`, plus an `O(n)` pass to compute the cost.
- **Space:** `O(1)` auxiliary space.

### Why This Works

After `nth_element`, the value at `nums[mid]` is the value that would occupy that index in a sorted array. Because the median is the only order statistic we need, the rest of the array does not need to be sorted.

The move count uses `long long`: the sum can exceed the range of `int` under the stated constraints. Casting before subtraction also prevents overflow when two input values are far apart.

---

## Key Takeaways

- The median minimizes a sum of absolute distances; the mean is associated with squared distances instead.
- Identify the exact information an algorithm needs. If it needs only one order statistic, selection can avoid a full sort.
- `std::nth_element` rearranges its input, so callers should account for that mutation.
- Use a wide type for both the difference and the accumulated total when constraints permit large values.

---

## References and Further Reading

- [LeetCode 462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)
- [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element)
- [Median](https://en.wikipedia.org/wiki/Median)

### Related LeetCode Problems

- [453. Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/): A related problem with a different allowed move.

### Patterns Used

- Median and absolute-distance minimization
- Order-statistic selection
