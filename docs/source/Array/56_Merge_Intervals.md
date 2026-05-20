# 56. Merge Intervals

## Problem Statement

Given an array of intervals where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

### Examples

```
Input:  intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: [1,3] and [2,6] overlap, merge them into [1,6].

Input:  intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: [1,4] and [4,5] are considered overlapping.

Input:  intervals = [[4,7],[1,4]]
Output: [[1,7]]
Explanation: [1,4] and [4,7] are considered overlapping.
```

### Constraints

- `1 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^4`

---

## First Intuition

The problem sounds simple enough: go through the intervals, find the ones that overlap, and fuse them together. That's a reasonable first instinct, and it leads naturally to a brute-force approach.

Before jumping to code, it helps to nail down exactly what "overlapping" means. Two intervals `[a, b]` and `[c, d]` overlap if one of them starts before the other ends. Touching at a single point counts too, as the second example shows: `[1,4]` and `[4,5]` merge into `[1,5]`.

One clean way to check overlap: take the span of both intervals combined (from the smallest start to the largest end), and compare it against the sum of their individual lengths. If the combined span is no larger than the total length, the two intervals must be covering some shared ground.

```
overlap when: (max_end - min_start) <= (b - a) + (d - c)
```

With that in hand, the most direct strategy is: for every interval, scan all the other intervals and merge anything that overlaps. Simple, but costly.

The inefficiency here is that you're repeatedly scanning the whole list for every element. And once you merge two intervals into one, the result might now overlap with something else further down, which makes the bookkeeping messy. That friction is the hint that something better exists.

The key observation is that overlapping intervals are only "adjacent" in a meaningful way when the input is sorted. If you sort by start time, you only ever need to look at the interval immediately before the current one. That single insight is what makes the optimal solution click.

---

## Approach 1: Brute Force

### Idea

The most literal reading of the problem: for each interval `i`, scan every interval `j` that comes after it. If they overlap, merge `j` to absorb `i`'s bounds, and mark `i` as consumed. At the end, collect everything that wasn't consumed.

The merge itself is straightforward: the merged interval spans from the minimum of the two starts to the maximum of the two ends.

One subtle thing here is the direction of the merge. When `i` and `j` overlap, we push the merged result into `j` (not `i`), because `j` might overlap with something even further ahead. By updating `j` in place, any subsequent comparison using `j` will automatically use the expanded bounds.

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        vector<bool> merged(intervals.size(), false);

        for (int i = 0; i < intervals.size(); i++) {
            for (int j = i + 1; j < intervals.size(); j++) {
                if (is_overlapped(intervals[i], intervals[j])) {
                    intervals[j][0] = min(intervals[i][0], intervals[j][0]);
                    intervals[j][1] = max(intervals[i][1], intervals[j][1]);
                    merged[i] = true;
                }
            }
        }

        for (int i = 0; i < intervals.size(); i++) {
            if (!merged[i]) result.push_back(intervals[i]);
        }
        return result;
    }

    bool is_overlapped(const vector<int>& a, const vector<int>& b) {
        int min_start = min(a[0], b[0]);
        int max_end   = max(a[1], b[1]);
        return (max_end - min_start) <= (a[1] - a[0] + b[1] - b[0]);
    }
};
```

### Complexity

- **Time:** `O(N^2)`. Two nested loops over all intervals.
- **Space:** `O(N)` for the `merged` boolean array.

### Limitations

The nested loop is the obvious problem. But there's a subtler issue too: the input isn't sorted, so you can't guarantee that once you've processed interval `i`, you won't need to revisit it. For example, if the input is `[[4,7],[1,4]]`, interval `i=0` is `[4,7]` and `j=1` is `[1,4]`. They do overlap, so the result (`[1,7]`) gets pushed into `j`. But `i` is marked as consumed even though it started at 4, which is fine here. The logic holds, but it's easy to convince yourself it might not in some edge case.

The right fix is to sort the input first. Once sorted by start time, overlapping intervals are always neighbors, and you never need to look back.

---

## Approach 2: Sort (Optimal)

### Idea

After sorting by start time, a crucial property holds: if interval `i` doesn't overlap with interval `i-1`, it won't overlap with anything before `i-1` either (because everything before has an even smaller start). So you only ever need to compare each interval with the one immediately preceding it.

The merge condition simplifies nicely: after sorting, `intervals[i][0] >= intervals[i-1][0]` is always true. So the only question is whether `intervals[i][0] <= intervals[i-1][1]`. If the current interval starts before the previous one ends, they overlap.

When they do overlap, merge them into `intervals[i]` (so the next comparison uses the expanded bounds), and mark `intervals[i-1]` as consumed.

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        vector<bool> merged(intervals.size(), false);

        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= intervals[i-1][1]) {
                intervals[i][0] = intervals[i-1][0];
                intervals[i][1] = max(intervals[i-1][1], intervals[i][1]);
                merged[i-1] = true;
            }
        }

        vector<vector<int>> result;
        for (int i = 0; i < intervals.size(); i++) {
            if (!merged[i]) result.push_back(intervals[i]);
        }
        return result;
    }
};
```

Let's trace through the first example to make sure it's clear:

```
Input (sorted): [[1,3],[2,6],[8,10],[15,18]]

i=1: [2,6] vs [1,3] → 2 <= 3, overlap → merge into [1,6], mark [1,3] consumed
i=2: [8,10] vs [1,6] → 8 > 6, no overlap
i=3: [15,18] vs [8,10] → 15 > 10, no overlap

Result: [[1,6],[8,10],[15,18]]  ✓
```

And the chain-merge case, `[[1,4],[2,5],[3,6]]`:

```
i=1: [2,5] vs [1,4] → overlap → merge into [1,5], mark [1,4] consumed
i=2: [3,6] vs [1,5] → overlap → merge into [1,6], mark [1,5] consumed

Result: [[1,6]]  ✓
```

Because each merge propagates into `intervals[i]`, a chain of overlapping intervals collapses correctly in a single pass.

### Complexity

- **Time:** `O(N log N)` for sorting, then `O(N)` for the single scan. Overall `O(N log N)`.
- **Space:** `O(N)` for the `merged` array and the result.

This is the optimal solution. Sorting is the key that reduces the problem from `O(N^2)` comparisons to a single linear pass.

---

## Key Takeaways

- When dealing with intervals, **sort by start time** first. It's the most common unlock, and it transforms a messy all-pairs comparison into a clean linear scan.
- The overlap check `intervals[i][0] <= intervals[i-1][1]` is only valid after sorting. Without sorting, this comparison would miss non-adjacent overlaps.
- When merging, always propagate the result forward (into `intervals[i]`) so the next comparison sees the expanded bounds. This handles chain merges like `[1,4],[2,5],[3,6]` correctly in one pass.
- The `max` in `intervals[i][1] = max(intervals[i-1][1], intervals[i][1])` is easy to overlook. If the current interval is fully contained inside the previous one (e.g., `[1,10]` and `[2,5]`), you want to keep the larger end, not overwrite it.

---

## References and Further Reading

### Related LeetCode Problems

- [57. Insert Interval](https://leetcode.com/problems/insert-interval/): Insert a new interval into a sorted, non-overlapping list and merge if necessary, a natural follow-up.
- [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/): Find the minimum number of intervals to remove to make the rest non-overlapping.
- [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms/): Determine if a person can attend all meetings, uses the same sort-by-start trick.
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/): Find the minimum number of meeting rooms required.

### Patterns Used

- Sort by start time to reduce interval problems to a linear scan
- In-place merge by propagating expanded bounds forward through the array

### Concepts Worth Reviewing

- Why sorting unlocks greedy approaches: once order is established, local comparisons become globally correct
- The containment edge case: when one interval is fully inside another, the merge must preserve the outer endpoint