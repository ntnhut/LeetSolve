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

Suppose we choose a target value `M`. Every element `nums[i]` takes `|nums[i] - M|` moves to reach it, so the total is the sum of those distances.

Choosing a target near the middle feels promising: moving the target toward one end makes some elements closer, but makes the elements on the other side farther away. The value that balances those effects is the median, not necessarily the mean. Sorting makes the median easy to identify, and then we can add up each element's distance from it.

Once we know that only the median is needed, we can improve on fully sorting the array. The second approach uses `std::nth_element` to place the median in its sorted position without ordering every other element.

---

## Approach 1: Sort and Choose the Median

### Idea

Sort the values and choose the middle one as the target. For an even-sized array, choosing either of the two middle values minimizes the total distance; `nums[n / 2]` selects the upper middle value.

Why does a median minimize the sum of absolute distances? Imagine moving the target one step to the right. Every value on the left becomes one step farther away, while every value on the right becomes one step closer. To the left of a median, at least as many values lie to the right as to the left, so shifting right cannot increase the total cost. To the right of a median, at least as many values lie to the left as to the right, so shifting farther right cannot reduce the cost. The same reasoning applies when shifting left.

For example, for `[0,1,2,2,10]`, the median is `2`, and the cost is `2 + 1 + 0 + 0 + 8 = 11`. Choosing the mean, `3`, costs `3 + 2 + 1 + 1 + 7 = 14`.

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
- **Space:** `O(1)` auxiliary space, excluding any implementation-specific storage used by sorting.

### Limitations

Sorting determines the order of every element, but the cost calculation only needs the median. We can avoid doing that extra ordering work.

---

## Approach 2: Select the Median with `std::nth_element`

### Idea

`std::nth_element` rearranges the array so the element at a chosen position is the one that would occupy that position in a fully sorted array. Values before it are no greater, and values after it are no smaller, but neither side is fully sorted.

That is enough here. We select the element at index `n / 2`, then calculate the distance from each value to that median just as before. This improves the average running time from `O(n log n)` to `O(n)`.

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

- **Time:** `O(n)` on average for selection, followed by an `O(n)` pass to sum the distances.
- **Space:** `O(1)` auxiliary space.

### Why This Works

We do not rely on the array being fully sorted. `nth_element` guarantees that `nums[mid]` has the same value it would have at that position after sorting. Since the median is all we need, partitioning is sufficient.

The accumulated move count uses `long long` so it can represent totals larger than a 32-bit integer, and the subtraction is widened before taking the absolute value.

---

## Key Takeaways

- The median minimizes the sum of absolute distances. The mean is the minimizer for squared distances, which is a different objective.
- Check what information the next step actually needs. If it only needs an order statistic, full sorting may be unnecessary.
- `std::nth_element` mutates the input and partitions it around the selected position, but does not sort either partition.
- Widen values before subtraction and accumulation when the constraints allow totals beyond the range of `int`.

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
