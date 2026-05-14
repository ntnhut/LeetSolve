# 901. Online Stock Span

## Problem Statement

Design an algorithm that collects daily price quotes for some stock and returns the **span** of that stock's price for the current day.

The span of the stock's price in one day is the maximum number of **consecutive days** (starting from that day and going backward) for which the stock price was **less than or equal to** the price of that day.

### Example 1
If the prices of the stock in the last four days is `[7, 2, 1, 2]` and the price today is `2`, then the span is `4`: all four days (including today) have a price ≤ 2.

### Example 2
If the prices of the last four days is `[7, 34, 1, 2]` and the price today is `8`, then the span is `3`: today (8), the day before (2), and the day before that (1) are all ≤ 8. But day four had price 34 > 8, so we stop.

### Interface to implement

```
StockSpanner()           // Initializes the object
int next(int price)      // Returns the span for today's price
```

### Example trace

```
Input:  [100, 80, 60, 70, 60, 75, 85]
Output: [  1,  1,  1,  2,  1,  4,  6]
```

### Constraints
- `1 <= price <= 10^5`
- At most `10^4` calls will be made to `next`

---

## First Intuition

When you read this problem, the first thing that feels natural is: *look backward*.

For each new price, you want to count how many consecutive previous prices are ≤ today's price. That's the definition of span. And the most direct way to answer "how many things satisfy this condition looking backward?" is to just... look backward. Iterate from the current day toward the past and count as long as the condition holds.

This is a completely reasonable starting point. If you've ever counted a winning streak in sports stats, or tracked how many days in a row the temperature was above some threshold, you've done exactly this kind of backward scan.

The naive idea: keep a history of all prices, and every time a new price comes in, scan backward through that history until you hit a price that breaks the ≤ condition.

It works. But you'll quickly realize that in the worst case, you're scanning the entire history for every new price. That's `O(N)` per call, and `O(N^2)` overall if you make `N` calls. For `N = 10^4`, that's 100 million operations, acceptable perhaps, but far from elegant.

The interesting question is: *can we avoid re-scanning the same prices over and over?*

That's where the insight starts to build.

---

## Approach 1: Linked List (Brute Force)

### Idea

The most direct implementation of the naive intuition: maintain a list of all prices seen so far, and for each new price, iterate from the most recent backward, counting how many consecutive prices are ≤ today's price.

We use a `std::list` with front-insertion so the most recent price is always at the beginning. Then we walk the list forward (which corresponds to walking backward in time) as long as `*it <= price`.

### Code

```cpp
class StockSpanner {
private:
    list<int> prices;
public:
    StockSpanner() {}

    int next(int price) {
        prices.push_front(price);
        int span = 0;
        auto it = prices.begin();
        while (it != prices.end() && *it <= price) {
            span++;
            it++;
        }
        return span;
    }
};
```

### Complexity

- **Time:** `O(N)` per `next()` call in the worst case (e.g., prices are strictly increasing). Over `N` calls, that's `O(N^2)` total.
- **Space:** `O(N)` to store all prices.

### Limitations

This approach is correct but inefficient. The linked list has poor cache locality compared to arrays, and every call potentially scans the entire history. We can do better on both fronts.

---

## Approach 2: Fixed Array

### Idea

Same logic as before, but we replace the linked list with a plain fixed-size array. Since the problem guarantees at most `10^4` calls, we can preallocate `prices[10000]` and maintain an index `i`.

For each new price, we store it at `prices[i]`, then scan backward from index `i` counting as long as `prices[k] <= price`.

### Code

```cpp
class StockSpanner {
private:
    int prices[10000];
    int i;
public:
    StockSpanner() : i(0) {}

    int next(int price) {
        prices[i] = price;
        int span = 0;
        for (int k = i; k != -1 && prices[k] <= price; k--) {
            span++;
        }
        i++;
        return span;
    }
};
```

### Complexity

- **Time:** Still `O(N)` per call in the worst case. The logic is identical to Approach 1.
- **Space:** `O(N)` fixed allocation upfront, no dynamic memory overhead.

### Limitations

This is cleaner and faster in practice (better cache behavior, no pointer chasing), but it still doesn't solve the fundamental algorithmic inefficiency. We're still re-examining prices that we've already "accounted for."

That's the key observation that leads to the optimal approach.

---

## Approach 3: Monotonic Stack (Optimal)

### Idea

Here's the insight that unlocks the efficient solution.

Think about what happens when a new price comes in and it's *larger* than several previous prices. Say the history ends in `[50, 30, 20, 40]` and the new price is `60`. We scan back: `40 <= 60` ✓, `20 <= 60` ✓, `30 <= 60` ✓, `50 <= 60` ✓. All four contribute to the span.

Now here's the thing: once `60` is in the history and a future price of, say, `65` arrives, those four days behind `60` will *again* be included in `65`'s span. We're recounting them.

What if, instead of storing just the raw price, we stored *[price, how many days this price already covers]*? That way, when `65` arrives and asks "does `60` qualify?", we don't just get `yes`, we get "yes, and `60` already covers 5 days behind it." We can skip directly past all of them.

This is exactly the monotonic stack approach. We maintain a stack of `(price, span)` pairs. The stack stays **monotonically decreasing** in price: if a new price comes in that's >= the stack top, we pop that entry and absorb its span into ours.

```
Prices seen:     100  80   60   70   60   75   85
                  ↑    ↑    ↑    ↑    ↑    ↑    ↑

After next(100): stack = [(100, 1)]              → span = 1
After next(80):  stack = [(100,1), (80,1)]       → span = 1
After next(60):  stack = [(100,1), (80,1),(60,1)]→ span = 1
After next(70):  pop (60,1) → span = 1 + 1 = 2
                 stack = [(100,1),(80,1),(70,2)] → span = 2
After next(60):  stack = [(100,1),(80,1),(70,2),(60,1)]→ span = 1
After next(75):  pop (60,1)→ span=2, pop (70,2)→ span=4
                 stack = [(100,1),(80,1),(75,4)] → span = 4
After next(85):  pop (75,4)→ span=5, pop (80,1)→ span=6
                 stack = [(100,1),(85,6)]        → span = 6
```

Notice that prices that are "covered" by a later larger price get popped off entirely. They'll never be individually revisited again.

### Code

```cpp
class StockSpanner {
private:
    stack<pair<int, int>> prices_spans;
public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;
        while (!prices_spans.empty() && price >= prices_spans.top().first) {
            span += prices_spans.top().second;
            prices_spans.pop();
        }
        prices_spans.push({price, span});
        return span;
    }
};
```

### Complexity

- **Time:** `O(1)` amortized per `next()` call. Each price is pushed onto the stack exactly once and popped at most once. So across `N` calls, the total number of push/pop operations is at most `2N`, that's `O(N)` total, or `O(1)` amortized per call.
- **Space:** `O(N)` in the worst case (when prices are strictly decreasing, nothing ever gets popped).

### The "aha moment"

The key insight is that you don't need individual price history if you can compress it. Once a price has been "absorbed" into a larger span, it will never be the bottleneck again, the larger price already carries that information forward. The monotonic stack is just a way to maintain only the prices that are still *potentially* relevant as future blockers.

---

## Key Takeaways

- **Monotonic stacks are the right tool when you need "next greater/smaller" relationships** or when you're aggregating backward spans. If you ever find yourself re-scanning the same region of an array, a monotonic structure can often help you skip it.

- **Storing computed results alongside the raw value** (like storing `span` with `price`) is a powerful trick. It lets later queries skip over large chunks of already-processed history in a single step.

- **Amortized analysis matters here.** The individual worst-case for a single `next()` call is `O(N)` (if the stack is full and everything gets popped). But since each element is pushed/popped at most once across all calls, the *total* work is `O(N)`, making the per-call *amortized* cost `O(1)`.

- **Progressive refinement pays off.** Starting with the brute-force scan (Approach 1), moving to a cleaner array (Approach 2), and then observing the redundant re-scanning (Approach 3) is a natural thought process. Don't skip directly to the optimal, the earlier steps show you *why* the optimization is needed.

- **Common pitfall:** Forgetting to initialize `span = 1` before the while loop. Today's price always spans at least itself.

---

## References & Further Reading

### Related LeetCode problems

- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/): "next greater element" using a monotonic stack; nearly identical pattern
- [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/): foundational monotonic stack problem
- [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/): classic hard-level monotonic stack application
- [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/): aggregating span-like contributions across subarrays

### Patterns to study

- **Monotonic Stack**: used whenever you need efficient "previous/next greater or smaller" queries; amortized `O(1)` per element
- **Amortized Analysis**: understanding why an `O(N)` worst-case single call can still yield `O(1)` average across all calls
- **Online Algorithms**: processing input one element at a time without seeing the future; this problem is a classic example