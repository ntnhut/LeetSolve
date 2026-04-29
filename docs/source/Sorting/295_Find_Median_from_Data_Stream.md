# 295. Find Median from Data Stream

## Problem Statement

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

- For example, for `arr = [2, 3, 4]`, the median is `3`.
- For example, for `arr = [2, 3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the `MedianFinder` class:

- `MedianFinder()` initializes the `MedianFinder` object.
- `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
- `double findMedian()` returns the median of all elements so far. Answers within `10^-5` of the actual answer will be accepted.

### Example 1

```
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr = [1, 2, 3]
medianFinder.findMedian(); // return 2.0
```

### Constraints

- `-10^5 <= num <= 10^5`
- There will be at least one element in the data structure before calling `findMedian`.
- At most `5 * 10^4` calls will be made to `addNum` and `findMedian`.

### Follow-up

- If all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?
- If 99% of all integer numbers from the stream are in the range `[0, 100]`, how would you optimize your solution?

---

## Intuition

The brute-force idea is simple: keep all elements in a list, sort it on every `findMedian()` call, and read off the middle value(s). This works, but sorting is expensive — it throws away all prior ordering work on every call.

From there, the natural question becomes: **can we keep the list sorted at all times?** If so, `findMedian()` becomes a cheap index lookup, and we pay only for the cost of inserting each new element in the right place.

Pushing further: do we actually need _every_ element sorted? The median only cares about the one or two values right in the middle of the ordered sequence. That observation leads to the most elegant solution — splitting the data into a **left half** and a **right half**, maintaining only their extremes (max of left, min of right) using heaps.

Let's walk through each approach in order of increasing sophistication.

---

## Solution 1: Sorted Vector — Brute Force

The simplest approach: just append every new number and sort the entire array whenever `findMedian()` is called.

```cpp
class MedianFinder {
private:
    vector<int> arr;
public:
    MedianFinder() {
        arr.reserve(50000);
    }

    void addNum(int num) {
        arr.push_back(num);
    }

    double findMedian() {
        std::sort(arr.begin(), arr.end());
        int midIdx = arr.size() / 2;
        if (arr.size() % 2 == 1) {
            return arr[midIdx];
        } else {
            return (static_cast<double>(arr[midIdx]) + arr[midIdx - 1]) / 2.0;
        }
    }
};
```

`arr.reserve(50000)` pre-allocates the maximum possible capacity upfront, eliminating all heap reallocations during `push_back`. Since the problem guarantees at most `5 × 10^4` calls, this is safe and avoids the hidden O(N) cost of reallocation.

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `addNum`  | O(1) amortized | — |
| `findMedian` | O(N log N) | O(N) |

The bottleneck is `findMedian()`: every call re-sorts the full array from scratch, discarding all previous ordering work. This is wasteful — if you call `findMedian()` frequently, you are doing `O(N log N)` work each time.

---

## Solution 2: `std::nth_element()` — Partial Sort

A key insight: the median only depends on the value(s) at the middle index (or two middle indices). We don't need every element in sorted order — we just need the correct element placed at the correct position.

`std::nth_element()` does exactly this. It partially rearranges the array so that:
- The element at position `n` is the element that would be there if the array were fully sorted.
- All elements to its left are ≤ it, and all elements to its right are ≥ it (but neither side is necessarily sorted).

This runs in **O(N)** average time — much faster than O(N log N) full sort.

```cpp
class MedianFinder {
private:
    vector<int> arr;
public:
    MedianFinder() {
        arr.reserve(50000);
    }

    void addNum(int num) {
        arr.push_back(num);
    }

    double findMedian() {
        int midIdx = arr.size() / 2;
        std::nth_element(arr.begin(), arr.begin() + midIdx, arr.end());
        double median = arr[midIdx];

        if (arr.size() % 2 == 1) {
            return median;
        } else {
            // For the even case, we also need arr[midIdx - 1].
            // We only need to partition the LEFT half of the array,
            // since arr[midIdx] is already in place.
            std::nth_element(arr.begin(), arr.begin() + midIdx - 1, arr.begin() + midIdx);
            return (static_cast<double>(arr[midIdx - 1]) + median) / 2.0;
        }
    }
};
```

For the even-length case, we call `nth_element` a second time to find `arr[midIdx - 1]`. The key optimization is the third argument: `arr.begin() + midIdx` instead of `arr.end()`. This restricts the second partition to only the left half of the array, reducing work from O(N) to O(N/2).

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `addNum`  | O(1) amortized | — |
| `findMedian` | O(N) average (O(1.5N) with the range optimization) | O(N) |

Note that `std::nth_element` uses introselect internally, guaranteeing O(N) worst-case on modern implementations, not just on average.

---

## Solution 3: `std::multiset` — Always Sorted

What if we keep the elements sorted at all times, so `findMedian()` never has to sort anything? A `std::multiset` (a balanced BST) does this: every insertion maintains sorted order in O(log N).

```cpp
class MedianFinder {
private:
    multiset<int> arr;
public:
    MedianFinder() {}

    void addNum(int num) {
        arr.insert(num);
    }

    double findMedian() {
        int N = arr.size();
        auto it = arr.begin();
        std::advance(it, N / 2);
        double median = *it;

        if (N % 2 == 1) {
            return median;
        } else {
            std::advance(it, -1);
            return (static_cast<double>(*it) + median) / 2.0;
        }
    }
};
```

`std::advance(it, N/2)` walks the iterator forward by N/2 steps. Unlike a vector, a `multiset` is backed by a tree with non-contiguous memory, so there is no O(1) random access. You cannot write `*(arr.begin() + arr.size() / 2)` — iterators must be stepped one node at a time.

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `addNum`  | O(log N) | — |
| `findMedian` | O(N/2) = O(N) | O(N) |

`addNum` is now faster than before, but `findMedian` is still O(N) due to the iterator traversal. In practice, the pointer-chasing through a non-contiguous BST is also cache-unfriendly, making constant factors worse than a vector-based approach despite the same asymptotic complexity.

---

## Solution 4: Two Heaps — Optimal

Let's think about what the median really is structurally:

- It is the **maximum** of the left half of the sorted array.
- It is the **minimum** of the right half of the sorted array.

We don't need the entire sorted order — we only need the top of each half. This is exactly what heaps provide in O(1).

The idea: maintain two heaps that together partition all elements seen so far.
- `left`: a **max-heap** holding the smaller half of all elements.
- `right`: a **min-heap** holding the larger half of all elements.

**Invariants we maintain:**
1. Every element in `left` ≤ every element in `right`.
2. `left.size()` is either equal to `right.size()` (even total) or exactly one more (odd total).

Under these invariants:
- If odd total: median = `left.top()`.
- If even total: median = `(left.top() + right.top()) / 2.0`.

**Insertion logic** to maintain both invariants:

```
push num → left (max-heap)
move left.top() → right    // ensures cross-heap ordering
if right.size() > left.size():
    move right.top() → left  // re-balance size
```

This three-step dance ensures that after every insertion, the size and ordering invariants are preserved.

```cpp
class MedianFinder {
private:
    priority_queue<int> left;                               // max-heap
    priority_queue<int, vector<int>, greater<int>> right;  // min-heap
public:
    MedianFinder() {}

    void addNum(int num) {
        left.push(num);
        right.push(left.top());
        left.pop();
        if (left.size() < right.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        if (left.size() == right.size())
            return (static_cast<double>(left.top()) + right.top()) / 2.0;
        return left.top();
    }
};
```

### Why the insertion order works

Pushing `num` to `left` first and then immediately moving `left.top()` to `right` — rather than deciding which heap to push to directly — is a clean trick that avoids branching. It guarantees the ordering invariant: whatever `num` is, the largest element of the left half always flows to the right heap first, keeping `left.top() ≤ right.top()` without an explicit comparison.

### Complexity

| Operation | Time | Space |
|-----------|------|-------|
| `addNum`  | O(log N) | — |
| `findMedian` | **O(1)** | O(N) |

This is the optimal solution for the general case. `findMedian` is now constant time, and each insertion costs only O(log N) — comparable to `multiset` but with much better cache performance due to the contiguous heap storage.

---

## Solution Comparison

| Solution | `addNum` | `findMedian` | Notes |
|---|---|---|---|
| Sorted vector | O(1) | O(N log N) | Simple, slow for frequent median queries |
| `nth_element` | O(1) | O(N) | Better; rearranges array in-place |
| `multiset` | O(log N) | O(N) | Always sorted; slow iterator traversal |
| Two heaps | O(log N) | **O(1)** | Optimal for general case |

---

## Follow-up

### 1. All numbers in `[0, 100]`

When the value range is bounded and small, we can replace heaps with a **counting array** (bucket array). Keep an array `cnt[101]` where `cnt[x]` is the number of times `x` has appeared.

**Idea:** To find the median, walk the cumulative count until you reach the middle rank(s). Since the range is fixed at 101 values, this scan is always O(101) = O(1) in practice.

```cpp
class MedianFinder {
private:
    int cnt[101] = {};
    int total = 0;
public:
    MedianFinder() {}

    void addNum(int num) {
        cnt[num]++;
        total++;
    }

    double findMedian() {
        int mid1 = (total + 1) / 2;   // lower median rank (1-indexed)
        int mid2 = (total + 2) / 2;   // upper median rank (same as mid1 if odd)

        int running = 0;
        int val1 = -1, val2 = -1;
        for (int i = 0; i <= 100; i++) {
            running += cnt[i];
            if (val1 == -1 && running >= mid1) val1 = i;
            if (val2 == -1 && running >= mid2) val2 = i;
            if (val1 != -1 && val2 != -1) break;
        }
        return (val1 + val2) / 2.0;
    }
};
```

**Why this is better:**
- `addNum`: O(1) — just increment a counter.
- `findMedian`: O(101) = O(1) — fixed-range scan.
- Space: O(101) = O(1) — constant regardless of stream length.
- Cache-friendly: sequential array access is extremely fast in practice.

### 2. 99% of numbers in `[0, 100]`

When a small fraction of numbers fall outside `[0, 100]`, use a **hybrid** approach:
- A `cnt[101]` bucket array for in-range numbers `[0, 100]`.
- A max-heap `leftOutliers` for numbers `< 0`.
- A min-heap `rightOutliers` for numbers `> 100`.
- A running `total` count.

```cpp
class MedianFinder {
private:
    int cnt[101] = {};
    priority_queue<int> leftOutliers;                               // max-heap for < 0
    priority_queue<int, vector<int>, greater<int>> rightOutliers;  // min-heap for > 100
    int total = 0;

public:
    MedianFinder() {}

    void addNum(int num) {
        if (num < 0)        leftOutliers.push(num);
        else if (num > 100) rightOutliers.push(num);
        else                cnt[num]++;
        total++;
    }

    double findMedian() {
        int mid1 = (total + 1) / 2;
        int mid2 = (total + 2) / 2;

        // Helper lambda: find the value at a given rank (1-indexed)
        auto findRank = [&](int rank) -> double {
            // Check left outliers (negatives, stored as max-heap)
            // We need to count how many left outliers exist
            int leftCount = (int)leftOutliers.size();
            if (rank <= leftCount) {
                // Need the rank-th smallest among left outliers.
                // Since we only need the median, and 99% are in-range,
                // outliers are rare — copy and sort for simplicity.
                vector<int> tmp;
                auto pq = leftOutliers;
                while (!pq.empty()) { tmp.push_back(pq.top()); pq.pop(); }
                std::sort(tmp.begin(), tmp.end());
                return tmp[rank - 1];
            }
            rank -= leftCount;

            // Check in-range bucket [0, 100]
            for (int i = 0; i <= 100; i++) {
                if (rank <= cnt[i]) return i;
                rank -= cnt[i];
            }

            // Check right outliers (positives > 100, stored as min-heap)
            vector<int> tmp;
            auto pq = rightOutliers;
            while (!pq.empty()) { tmp.push_back(pq.top()); pq.pop(); }
            std::sort(tmp.begin(), tmp.end());
            return tmp[rank - 1];
        };

        return (findRank(mid1) + findRank(mid2)) / 2.0;
    }
};
```

**Complexity:**
- `addNum`: O(1) for in-range values; O(log M) for outliers (where M = number of outliers).
- `findMedian`: O(101) in the common case (99% of the time, the median falls inside `[0, 100]`). Rare O(M log M) for edge cases where the median falls in the outlier region.

**Practical takeaway:**
- For strict `[0, 100]`: the counting array is optimal.
- For 99% in-range: the hybrid approach gives near-O(1) median queries while correctly handling outliers.

---

## Key Takeaways

- **Know your data structure trade-offs.** `std::multiset` keeps elements sorted on every insert (O(log N)), but its tree-based non-contiguous memory makes random access impossible — you must use `std::advance()` and pay O(N) to reach the middle element. `std::priority_queue` uses a contiguous heap array, making `top()` an O(1) operation and benefiting from CPU cache locality.

- **Partial algorithms beat full algorithms when you don't need full information.** `std::nth_element()` is a powerful primitive that places the k-th element correctly in O(N), without sorting the rest of the array. Reach for it whenever you only need rank-based values (median, percentiles) rather than a fully sorted sequence.

- **Invariant-driven design simplifies complex data structures.** The two-heap solution is built on one simple invariant: the max of the left half is always ≤ the min of the right half, and the sizes differ by at most one. Maintaining this invariant on every `addNum` makes `findMedian` trivially O(1).

- **Bounded input ranges unlock O(1) algorithms.** When values are constrained to a small fixed range, counting arrays replace comparison-based structures entirely. Scanning 101 buckets is not just asymptotically O(1) — it is also cache-optimal and branch-predictor friendly in practice.

- **Hybrid structures handle the 99%/1% case elegantly.** When most inputs are bounded but outliers exist, combining a fast in-range structure (counting array) with small auxiliary structures (heaps) for edge cases is a practical engineering pattern. The common path stays fast; the rare path handles correctness.

- **`std::advance()` vs. pointer arithmetic.** With contiguous containers like `vector`, you can use `*(begin + k)` for O(1) access. With node-based containers like `multiset`, `list`, or `map`, you must use `std::advance(it, k)`, which steps the iterator one node at a time — O(k) cost. This distinction matters enormously at scale.

---

## References

- [LeetCode 295 — Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)
- [cppreference — `std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element)
- [cppreference — `std::multiset`](https://en.cppreference.com/w/cpp/container/multiset)
- [cppreference — `std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue)
- [cppreference — `std::advance`](https://en.cppreference.com/w/cpp/iterator/advance)
- [Wikipedia — Order statistic](https://en.wikipedia.org/wiki/Order_statistic)
- [Wikipedia — Introselect (nth_element algorithm)](https://en.wikipedia.org/wiki/Introselect)