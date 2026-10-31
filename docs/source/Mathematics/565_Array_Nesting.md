# 565. Array Nesting

## Problem Statement

You are given an integer array `nums` of length `n` where `nums` is a permutation of the numbers in the range `[0, n - 1]`.

You should build a set `s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ...}` subject to the following rules:

- The first element in `s[k]` starts with `nums[k]`.
- The next element is `nums[nums[k]]`, then `nums[nums[nums[k]]]`, and so on.
- Stop before adding a duplicate element to `s[k]`.

Return the length of the longest set `s[k]`.

### Example 1

```text
Input: nums = [5,4,0,3,1,6,2]
Output: 4
Explanation:
One of the longest sets is:
s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
```

### Example 2

```text
Input: nums = [0,1,2]
Output: 1
```

### Constraints

- `1 <= nums.length <= 10^5`
- `0 <= nums[i] < nums.length`
- All the values in `nums` are unique.

---

## First Intuition

Starting from an index, repeatedly use the current value as the next index. For example, with `nums = [5,4,0,3,1,6,2]`, starting at `0` follows:

```text
0 -> 5 -> 6 -> 2 -> 0
```

The sequence stops when it returns to a value already seen. A straightforward approach would track a separate set for each starting index, but that repeats work: if two starts belong to the same loop, they visit the same values.

The important constraint is that `nums` is a permutation. Every index has exactly one outgoing link and exactly one incoming link, so the links divide into disjoint cycles. We can traverse each cycle once, mark its values as visited, and keep the length of the longest one.

---

## Approach: Traverse Each Permutation Cycle Once

### Idea

Interpret the array as a mapping from each index to the value stored at that index:

```text
index -> nums[index]
```

In Example 1, the mapping separates into these cycles:

```text
0 -> 5 -> 6 -> 2 -> 0
1 -> 4 -> 1
3 -> 3
```

Each set described by the problem is exactly one of these cycles, just written starting from a particular element. We iterate over all possible starting indices. If an index has not been visited, follow its cycle, marking each element and counting its length. Once the cycle closes, update the maximum. Since visited cycles are skipped, each index is processed only once.

### Code

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int arrayNesting(const vector<int>& nums) {
    int maxLen = 0;
    vector<bool> visited(nums.size(), false);

    for (int start = 0; start < static_cast<int>(nums.size()); start++) {
        if (visited[start]) {
            continue;
        }

        int len = 0;
        int current = start;
        while (!visited[current]) {
            visited[current] = true;
            current = nums[current];
            len++;
        }
        maxLen = max(maxLen, len);
    }

    return maxLen;
}

int main() {
    vector<int> nums{5, 4, 0, 3, 1, 6, 2};
    cout << arrayNesting(nums) << endl;
    nums = {0, 1, 2};
    cout << arrayNesting(nums) << endl;
    nums = {0, 2, 1};
    cout << arrayNesting(nums) << endl;
    nums = {2, 0, 1};
    cout << arrayNesting(nums) << endl;
}
```

```text
Output:
4
1
2
3
```

### Complexity

- **Time:** `O(n)`, because every index is visited at most once.
- **Space:** `O(n)` bits for the visited markers. `vector<bool>` is a specialized packed representation, but it still tracks one visited state per element.

### Why This Works

Because `nums` is a permutation, following links can never branch, and every chain must eventually return to a previously visited index. The resulting components are disjoint cycles. Marking each visited index ensures we count each cycle once, regardless of which element we encounter first.

---

## Key Takeaways

- An array of indices can represent a directed graph where each index has one outgoing edge.
- A permutation forms disjoint cycles, which can be traversed independently.
- Marking visited elements prevents repeated traversal and keeps the overall work linear.
- Make the traversal state explicit with a local `current` index rather than changing the loop variable or the input array.

---

## References and Further Reading

- [LeetCode 565. Array Nesting](https://leetcode.com/problems/array-nesting/)
- [Permutation](https://en.wikipedia.org/wiki/Permutation)

### Patterns Used

- Cycle decomposition
- Visited-state traversal
- Functional graphs
