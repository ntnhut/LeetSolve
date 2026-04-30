# 2034. Stock Price Fluctuation

## Problem Statement

You are given a stream of records about a particular stock. Each record contains a timestamp and the corresponding price of the stock at that timestamp.

Unfortunately, due to the volatile nature of the stock market, the records do not come in order. 

Even worse, some records may be incorrect. Another record with the same timestamp may appear later in the stream correcting the price of the previous wrong record.

Design an algorithm that:

- Updates the price of the stock at a particular timestamp, correcting the price from any previous records at the timestamp.
- Finds the latest price of the stock based on the current records.
- Finds the maximum price the stock has been based on the current records.
- Finds the minimum price the stock has been based on the current records.

**Implement the `StockPrice` class:**

- `StockPrice()`: Initializes the object with no price records.
- `void update(int timestamp, int price)`: Updates the price of the stock at the given timestamp.
- `int current()`: Returns the latest price of the stock.
- `int maximum()`: Returns the maximum price of the stock.
- `int minimum()`: Returns the minimum price of the stock.

**Example:**

```
Input:
["StockPrice", "update", "update", "current", "maximum", "update", "maximum", "update", "minimum"]
[[], [1, 10], [2, 5], [], [], [1, 3], [], [4, 2], []]

Output:
[null, null, null, 5, 10, null, 5, null, 2]
```

**Constraints:**

- `1 <= timestamp, price <= 10^9`
- At most `10^5` calls will be made in total to `update`, `current`, `maximum`, and `minimum`.
- `current`, `maximum`, and `minimum` will be called only after `update` has been called at least once.

---

## First Intuition

When you first read this problem, a few things stand out immediately.

The stock prices arrive out of order, and a timestamp can be corrected by a later record. So you can't just keep a running max or min; they might be invalidated at any point. 

That rules out any approach where you incrementally update a single value and never look back.

The most natural structure that comes to mind for storing timestamp-to-price mappings is a hash map. 

You probably thought: *"Let me just store every timestamp with its latest known price."* 

That's the right starting point. A hash map gives you `O(1)` updates and lets you handle corrections easily: just overwrite the old value.

For `current()`, you also need to track the latest timestamp. 

That's straightforward: keep a variable and update it whenever a new record comes in with a timestamp greater than or equal to what you've seen.

The challenge is `maximum()` and `minimum()`. Your first honest thought is probably: *"Just scan all the prices."* 

And that's a completely reasonable place to start. It works correctly. 

The question is only whether it's fast enough, and the answer depends on how often those calls are made.

Let's walk through both approaches.

---

## Approach 1: HashMap + Linear Scan

### Idea

Store all timestamp-price pairs in an unordered map. Track the latest timestamp and its price as you go. 

For `maximum()` and `minimum()`, just iterate over the entire map and find the answer.

### How I Thought About It

The update logic is clean. If a timestamp already exists in the map, the new price simply overwrites it. If the incoming timestamp is greater than or equal to `latest`, update `current`.

The `maximum()` and `minimum()` functions are honest brute force. There's no smarter structure here; just loop through every stored price and return the best one.

The reason this makes sense as a first attempt is that it requires almost no design overhead. You're solving the problem first, and worrying about optimization second.

### Code

```cpp
class StockPrice {
private:
    unordered_map<int, int> timedPrices;
    int cur, latest;

public:
    StockPrice() : cur(0), latest(0) {}

    void update(int timestamp, int price) {
        timedPrices[timestamp] = price;
        if (timestamp >= latest) {
            cur = price;
            latest = timestamp;
        }
    }

    int current() {
        return cur;
    }

    int maximum() {
        int max = cur;
        for (auto& t : timedPrices)
            if (t.second > max) max = t.second;
        return max;
    }

    int minimum() {
        int min = cur;
        for (auto& t : timedPrices)
            if (t.second < min) min = t.second;
        return min;
    }
};
```

### Complexity

- **Time:**
  - `update()`: `O(1)` average for the hash map insertion.
  - `current()`: `O(1)`.
  - `maximum()` / `minimum()`: `O(N)` where `N` is the number of unique timestamps stored.
- **Space:** `O(N)` for the hash map.

### Limitations

With up to 10^5 total calls, and if `maximum()` and `minimum()` are called frequently, you're looking at a lot of `O(N)` scans. 

In the worst case, alternating updates and max/min queries hits you hard. You need a way to answer min and max in sub-linear time.

---

## Approach 2: HashMap + Sorted Multiset

### What Improves

The key insight is simple: if you maintain the prices in a sorted order at all times, `maximum()` and `minimum()` become `O(1)`, just peek at the two ends.

The tricky part is handling corrections. When a timestamp is updated, the old price must be removed from the sorted structure and the new price inserted. 

This is where a `multiset` shines. It keeps elements sorted, supports duplicates (multiple timestamps can have the same price), and allows `O(log N)` insertion and deletion.

### How I Thought About It

You still need the hash map. Without it, when a correction comes in for a timestamp, you have no way of knowing what the old price was and you need the old price to remove it from the sorted structure.

So the flow during `update()` becomes:

1. Check if the timestamp already exists in the map.
2. If it does, remove the old price from the `multiset`.
3. Insert the new price into the `multiset`.
4. Update the map and track the latest timestamp as before.

One subtle but important point: when erasing from a `multiset`, use `sortedPrices.erase(sortedPrices.find(oldPrice))` instead of `sortedPrices.erase(oldPrice)`. 

The latter removes **all** elements with that value, which would incorrectly delete prices belonging to other timestamps.

```
Before update(1, 3):
  timedPrices: {1: 10, 2: 5}
  sortedPrices: {5, 10}

After update(1, 3):
  Remove 10 (old price for timestamp 1) from sortedPrices
  Insert 3
  timedPrices: {1: 3, 2: 5}
  sortedPrices: {3, 5}

maximum() -> *rbegin() = 5  (correct)
minimum() -> *begin()  = 3  (correct)
```

### Code

```cpp
class StockPrice {
private:
    unordered_map<int, int> timedPrices;
    multiset<int> sortedPrices;
    int cur, latest;

public:
    StockPrice() : cur(0), latest(0) {}

    void update(int timestamp, int price) {
        auto timeIt = timedPrices.find(timestamp);

        if (timeIt != timedPrices.end()) {
            sortedPrices.erase(sortedPrices.find(timeIt->second));
        }
        sortedPrices.insert(price);

        timedPrices[timestamp] = price;
        if (timestamp >= latest) {
            cur = price;
            latest = timestamp;
        }
    }

    int current() {
        return cur;
    }

    int maximum() {
        assert(!sortedPrices.empty());
        return *sortedPrices.rbegin();
    }

    int minimum() {
        assert(!sortedPrices.empty());
        return *sortedPrices.begin();
    }
};
```

### Complexity

- **Time:**
  - `update()`: `O(log N)` for `multiset` find, erase, and insert.
  - `current()`: `O(1)`.
  - `maximum()` / `minimum()`: `O(1)` by reading from the ends of the `multiset`.
- **Space:** `O(N)` for both the hash map and the multiset, each storing `N` prices.

---

## Final Optimal Approach

The second approach is the optimal one here. 

The key insight that unlocks it is recognizing that **you're solving two problems at once**: a lookup problem (what was the old price for this timestamp?) and a range problem (what is the current min/max?).

The hash map solves the lookup in `O(1)`. The `multiset` solves the range queries in `O(1)` and handles insertions/deletions in `O(log N)`. Together, they complement each other perfectly.

The trade-off is space: you're storing prices twice, once in the map and once in the set. But given the constraints (at most 10^5 entries), this is entirely acceptable.

The `multiset` is a natural fit here because prices are not unique, multiple timestamps can share the same price, and you need to handle each independently. 

A regular `set` would collapse duplicates and give wrong answers during removal.

---

## Key Takeaways

- **When min/max queries need to be fast on a dynamic dataset, think sorted structures.** A `multiset`, sorted array, or heap can maintain order as data changes.
- **Corrections are the subtle challenge here.** The moment a problem allows values to be updated retroactively, you need to track what the old value was before overwriting it.
- **Use `multiset::find()` before erasing, not `multiset::erase(value)`.** Erasing by value removes all duplicates. Erasing by iterator removes exactly one.
- **Two data structures serving different purposes can work together.** The hash map owns the ground truth; the multiset serves range queries. Neither is redundant.
- **Start with the brute-force.** The `O(N)` scan approach is correct and worth implementing first. It clarifies what information you actually have, which makes the optimization much clearer.

---

## References and Further Reading

**Related LeetCode problems:**

- [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/): Maintaining order in a dynamic stream using heaps.
- [1675. Minimize Deviation in Array](https://leetcode.com/problems/minimize-deviation-in-array/): Using `multiset` to track and reduce range dynamically.
- [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/): Another problem where a sorted multiset is the key tool.

**Patterns to review:**

- Sorted containers (`multiset`, `std::set`) for dynamic order statistics.
- The "two data structures" design pattern: one for `O(1)` lookup, one for efficient range queries.
- Heap-based approaches as an alternative when only one extreme (max or min) is needed.
