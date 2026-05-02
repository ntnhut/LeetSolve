# 2526. Find Consecutive Integers from a Data Stream

## Problem Statement

For a stream of integers, implement a data structure that checks if the last `k` integers parsed in the stream are equal to `value`.

Implement the `DataStream` class:

- `DataStream(int value, int k)` Initializes the object with an empty integer stream and the two integers `value` and `k`.
- `boolean consec(int num)` Adds `num` to the stream of integers. Returns `true` if the last `k` integers are equal to `value`, and `false` otherwise. If there are fewer than `k` integers, the condition does not hold true, so returns `false`.

**Example 1:**

```
Input
["DataStream", "consec", "consec", "consec", "consec"]
[[4, 3], [4], [4], [4], [3]]
Output
[null, false, false, true, false]

Explanation
DataStream dataStream = new DataStream(4, 3); // value = 4, k = 3
dataStream.consec(4); // Only 1 integer is parsed, so returns False.
dataStream.consec(4); // Only 2 integers are parsed.
                      // Since 2 is less than k, returns False.
dataStream.consec(4); // The 3 integers parsed are all equal to value, so returns True.
dataStream.consec(3); // The last k integers parsed in the stream are [4,4,3].
                      // Since 3 is not equal to value, it returns False.
```

**Constraints:**

- `1 <= value, num <= 10^9`
- `1 <= k <= 10^5`
- At most `10^5` calls will be made to `consec`.

## First Intuition

When you read "last `k` integers are all equal to `value`", the first instinct is to store everything. Just keep a queue or array of the last `k` elements, and on each call, check if all of them match `value`. That's the most direct translation of the problem description into code.

And honestly, that's not a bad starting point. It mirrors how you'd think about it by hand: slide a window of size `k` along the stream, peek inside, and check.

But pause for a second. You don't actually care *what* the last `k` numbers are. You only care *how many of them in a row* have been equal to `value`. That's a subtle but important shift. The moment a non-`value` number appears, the streak is broken and it doesn't matter what came before. You can throw away all that history.

This is the key insight: the problem reduces to tracking a **streak**, not a **window**.

## Approach: Counter (Streak Tracking)

### Idea

Instead of storing the last `k` numbers, just keep a running counter of how many consecutive `value`s you've seen so far.

Every time `consec(num)` is called:

- If `num == value`, increment the counter.
- If `num != value`, reset the counter to `0`.

Then simply check if the counter has reached `k`. If it has, the last `k` integers were all `value`, so return `true`. Otherwise, return `false`.

This works because the counter always reflects the current streak length. The moment a different number breaks the streak, the counter drops to zero and you start fresh. No memory of old values needed.

Here's how this plays out with the example:

```
value = 4, k = 3

consec(4) → count = 1 → 1 >= 3? No  → false
consec(4) → count = 2 → 2 >= 3? No  → false
consec(4) → count = 3 → 3 >= 3? Yes → true
consec(3) → count = 0 → 0 >= 3? No  → false
```

Clean and intuitive.

### Code

```cpp
class DataStream {
    int value;
    int k;
    int count;

public:
    DataStream(int value, int k) : value(value), k(k), count(0) {

    }

    bool consec(int num) {
        count = num == value ? count + 1 : 0;
        return count >= k;
    }
};
```

### Complexity

- **Time complexity:** `O(1)` per `consec` call. There's no loop, no traversal. Each call does a single comparison, an increment or reset, and another comparison. Constant work regardless of `k` or how many numbers have been streamed.
- **Space complexity:** `O(1)`. You store exactly three integers: `value`, `k`, and `count`. No array, no queue, no window buffer.


## Why This Is Better Than a Sliding Window

The naive sliding window approach would store a deque of the last `k` elements, push the new number in, pop the oldest one out, and scan to verify all elements match. That's `O(k)` space to hold the window and potentially `O(k)` time per call if you scan the whole window.

The counter approach gets you `O(1)` time and space by exploiting the structure of the problem. "All equal to `value`" is equivalent to "the streak hasn't been broken in the last `k` steps," and streaks only need a single number to track.

It's a good reminder that the most literal translation of a problem into code isn't always the best one. Reading more carefully often reveals that you need far less information than you think.


## Key Takeaways

- When a problem asks about "the last `k` elements all satisfying some condition," consider whether tracking a **streak counter** is sufficient instead of maintaining an actual window.
- A sliding window is useful when you need to know *what* the elements are. A counter is enough when you only need to know *how many in a row* pass a condition.
- Resetting a counter on failure is a classic pattern for consecutive/contiguous problems. It shows up in problems like "longest subarray with all 1s", "max consecutive ones", and similar variants.
- `O(1)` space is often achievable in streaming problems because streams are infinite by nature, and storing the full history is rarely necessary or feasible.

---

## References & Further Reading

**Related LeetCode Problems:**

- [485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/) — direct application of the same streak counter pattern
- [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) — streak tracking with a tolerance for flips
- [1446. Consecutive Characters](https://leetcode.com/problems/consecutive-characters/) — longest streak of a single repeated character
- [2348. Number of Zero-Filled Subarrays](https://leetcode.com/problems/number-of-zero-filled-subarrays/) — counting subarrays using streak length math

**Patterns:**

- **Streak / Run-length tracking:** Maintaining a counter that resets on failure is a fundamental pattern for any problem about "consecutive" or "in a row" elements.
- **Sliding window:** Worth knowing as the baseline comparison. When the window's actual contents matter, use it. When only its length or a property of the streak matters, the counter suffices.
- **Streaming / online algorithms:** Problems in a stream context reward `O(1)` space solutions. Storing history is often the wrong instinct.