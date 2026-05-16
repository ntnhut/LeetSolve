# 381. Insert Delete GetRandom O(1) - Duplicates Allowed

## Problem Statement

`RandomizedCollection` is a data structure that contains a collection of numbers, possibly with duplicates (i.e., a multiset). It should support inserting and removing specific elements and also reporting a random element.

Implement the `RandomizedCollection` class:

- `RandomizedCollection()`: Initializes the empty `RandomizedCollection` object.
- `bool insert(int val)`: Inserts an item `val` into the multiset, even if the item is already present. Returns `true` if the item was not present, `false` otherwise.
- `bool remove(int val)`: Removes an item `val` from the multiset if present. Returns `true` if the item is present, `false` otherwise. Note that if `val` has multiple occurrences, only one is removed.
- `int getRandom()`: Returns a random element from the current multiset. The probability of each element being returned is linearly proportional to its count in the multiset.

Each function must work in **average** `O(1)` time complexity.

### Example

```
Input:
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]

Output:
[null, true, false, true, 2, true, 1]

Explanation:
insert(1) → true  (1 not present before)
insert(1) → false (1 already exists; collection is now [1, 1])
insert(2) → true  (2 not present before; collection is now [1, 1, 2])
getRandom() → returns 1 with probability 2/3, or 2 with probability 1/3
remove(1)  → true (removes one 1; collection is now [1, 2])
getRandom() → returns 1 or 2, each with probability 1/2
```

### Constraints

- `-2^31 <= val <= 2^31 - 1`
- At most `2 * 10^5` calls total to `insert`, `remove`, and `getRandom`
- `getRandom` is only called when there is at least one element present

---

## First Intuition

When you first read this problem, `insert` and `remove` feel manageable. The one that stops you is `getRandom`.

For `getRandom` to return elements with probabilities proportional to their frequency, the simplest mental model is: imagine laying out all elements in a flat list, and just picking a random index. If `1` appears twice and `2` appears once in your list `[1, 1, 2]`, picking a random index naturally gives `1` a 2/3 probability. That's exactly the right behavior.

So the question becomes: can you maintain a flat array of all elements (with duplicates), where any index can be picked uniformly at random, while still supporting `O(1)` insert and remove?

Insert into an array is easy: just append to the end. That's `O(1)`.

Remove is the hard part. Removing from an arbitrary position in an array is `O(N)` because you'd need to shift elements. The classic trick to avoid this is the **swap-with-last** technique: instead of shifting, swap the element you want to remove with the last element, then pop the last element off. Now removal is `O(1)`, as long as you can find the element's index quickly.

That's the core insight the whole solution is built around. Everything else is bookkeeping to make that index lookup fast.

---

## Approach 1: `unordered_multiset`

### Idea

The most natural starting point is to reach for a data structure that handles duplicates out of the box: `unordered_multiset`. It supports insert, find, and erase by value directly.

For `getRandom`, you advance an iterator from the beginning by a random offset.

```cpp
class RandomizedCollection {
    unordered_multiset<int> s;
public:
    RandomizedCollection() {}
    
    bool insert(int val) {
        auto it = s.find(val);
        s.insert(it, val);
        return it == s.end();
    }
    
    bool remove(int val) {
        auto it = s.find(val);
        if (it == s.end()) return false;
        s.erase(it);
        return true;
    }
    
    int getRandom() {
        auto it = s.begin();
        advance(it, rand() % s.size());
        return *it;        
    }
};
```

### Complexity

- **Time:** `insert` and `remove` are `O(1)` average. But `getRandom` calls `std::advance`, which walks the iterator forward one step at a time, that's `O(N)`.
- **Space:** `O(N)` for the multiset.

### Limitations

The bottleneck is `getRandom`. An unordered container doesn't support random access by index, so you're forced to traverse from the beginning. This immediately disqualifies the approach for large inputs.

The key realization: you need a structure that supports true `O(1)` random access. That points directly to a plain array (or vector).

---

## Approach 2: Vector + Map of Priority Queues

### Idea

Now the core data structure is a `vector<int>` holding all values (with duplicates). `getRandom` becomes trivial: just pick `vals[rand() % vals.size()]`.

The challenge shifts to `remove`. You need to:
1. Find an index where `val` lives in the vector.
2. Swap that element with the last element.
3. Update the bookkeeping so the swapped element's new index is tracked.
4. Pop the last element off.

To find indices quickly, maintain an `unordered_map<int, ...>` that maps each value to its set of positions in the vector. Since `remove` only needs to pick one valid index (and you want to avoid index conflicts when swapping), a max-heap (priority queue) is used here to always grab the largest known index.

```cpp
class RandomizedCollection {
    vector<int> vals;
    unordered_map<int, priority_queue<int>> m;
public:
    RandomizedCollection() {}
    
    bool insert(int val) {
        bool rs = m.find(val) == m.end();
        vals.push_back(val);
        m[val].push(vals.size() - 1);
        return rs;
    }
    
    bool remove(int val) {
        auto it = m.find(val);
        if (it == m.end()) return false;

        // 1. Pick one index of val to remove (max index from heap)
        int idx_to_remove = it->second.top();

        // 2. Read the last element in the array
        int last = vals.back();

        // 3. Move last element into idx_to_remove
        //    Remove old last index from its heap, then add new index
        m[last].pop();
        m[last].push(idx_to_remove);
        vals[idx_to_remove] = last;

        // 4. Remove one occurrence of val from its heap
        it->second.pop();

        // 5. Clean up and shrink the array
        if (it->second.empty()) m.erase(it);
        vals.pop_back();
        return true;
    }
    
    int getRandom() {
        return vals[rand() % vals.size()];
    }
};
```

### Complexity

- **Time:** `insert` is `O(log N)` due to the heap push. `remove` is also `O(log N)`. `getRandom` is `O(1)`.
- **Space:** `O(N)`.

### Limitations

Using a max-heap was a reasonable instinct (always grab the farthest index to swap from), but heap operations are inherently `O(log N)`. We don't actually need ordering here. We just need *any* valid index for the value we're removing. A set, or even just any constant-time container, would be enough.

The "aha" is: drop the heap, use an `unordered_set` instead.

---

## Approach 3: Vector + Map of Unordered Sets (Optimal)

### Idea

Replace the priority queue with an `unordered_set<int>`. For each value, track all indices where it appears in the vector. When removing, just grab any index from the set (using `.begin()`), swap with the last element, and update the index sets.

The only tricky case is when the value being removed happens to be the same as the last element. In that case, you need to be careful: insert the new index before erasing the old one, or the set might become empty prematurely and you'd erase a wrong entry.

```cpp
class RandomizedCollection {
    vector<int> vals;
    unordered_map<int, unordered_set<int>> m;

public:
    RandomizedCollection() {}
    
    bool insert(int val) {
        bool is_new = m.find(val) == m.end() || m[val].empty();
        vals.push_back(val);
        m[val].insert(vals.size() - 1);
        return is_new;
    }
    
    bool remove(int val) {
        if (m.find(val) == m.end() || m[val].empty()) return false;
        
        // 1. Pick any index of the value to remove
        int idx_to_remove = *m[val].begin();
        m[val].erase(idx_to_remove);
        
        // 2. Grab the last element
        int last_val = vals.back();
        
        // 3. Move last element into the removed slot
        vals[idx_to_remove] = last_val;
        
        // 4. Update the index set for the moved element
        //    Insert new index before erasing old one, handles val == last_val correctly
        m[last_val].insert(idx_to_remove);
        m[last_val].erase(vals.size() - 1);
        
        // 5. Remove the last slot
        vals.pop_back();
        
        if (m[val].empty()) m.erase(val);
        
        return true;
    }
    
    int getRandom() {
        return vals[rand() % vals.size()];
    }
};
```

### Why the Order of Updates Matters

Step 4 has a subtle but important ordering requirement. If `val == last_val` (the element you're removing is the same as the last element), and you erase the old index before inserting the new one, you might accidentally empty the set and then try to update a value that's no longer tracked. Inserting first guarantees the set is never transiently empty during the swap.

### Complexity

- **Time:** `insert` is `O(1)` average. `remove` is `O(1)` average (unordered set insert/erase/lookup are all `O(1)` average). `getRandom` is `O(1)`.
- **Space:** `O(N)` for the vector and the map.

This is the optimal solution. All three operations run in `O(1)` average time.

---

## Key Takeaways

- The **swap-with-last** pattern is a fundamental trick for `O(1)` deletion from an array. When you see "remove in O(1) from a collection where order doesn't matter," think of this immediately.
- **`getRandom` in O(1)** requires a flat, index-accessible container like a vector. Any iterator-based traversal (as in `unordered_multiset`) will cost you `O(N)`.
- When you need to track multiple positions for duplicate values, a map of sets is the natural pairing with the swap-with-last strategy.
- The `val == last_val` edge case is easy to miss. Whenever you have a swap that updates two overlapping data structures simultaneously, think carefully about the order of operations.
- Upgrading from a priority queue to an unordered set is a meaningful optimization when you don't actually need ordering, it drops `O(log N)` to `O(1)`.

---

## References and Further Reading

### Related LeetCode Problems

- [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/): The no-duplicates version; a good warm-up before this problem
- [710. Random Pick with Blacklist](https://leetcode.com/problems/random-pick-with-blacklist/): Another problem requiring weighted/constrained random selection in `O(1)`

### Patterns Used

- Swap-with-last for `O(1)` deletion from unordered collections
- Index bookkeeping with hash maps to support fast lookups
- Multiset simulation using a vector and auxiliary map

### Concepts Worth Reviewing

- Amortized `O(1)` operations in hash-based containers
- Why random access requires contiguous memory (arrays vs. linked structures)
- Edge case handling in in-place swap operations with overlapping state