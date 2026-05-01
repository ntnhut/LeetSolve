# 146. LRU Cache

## Problem Statement

Design a data structure that follows the constraints of a **Least Recently Used (LRU)** cache.

Implement the `LRUCache` class:

- `LRUCache(int capacity)` — Initialize the LRU cache with positive size `capacity`.
- `int get(int key)` — Return the value of the key if it exists, otherwise return `-1`.
- `void put(int key, int value)` — Update the value if the key exists. Otherwise, add the key-value pair. If the number of keys exceeds capacity, **evict the least recently used key**.

Both `get` and `put` must each run in **`O(1)` average time complexity**.

**Example:**

```
Input:
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

Output:
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation:
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
```

**Constraints:**

- `1 <= capacity <= 3000`
- `0 <= key <= 10^4`
- `0 <= value <= 10^5`
- At most `2 * 10^5` calls will be made to `get` and `put`.

---

## First Intuition

Before we jump to code, let's make sure we fully understand what "least recently used" actually means in practice.

**Two things to internalize first:**

- "Used" includes both `get()` and `put()`. Any interaction with a key counts as a recent use.
- At any point in time, the cache has a clear ordering: some key was touched most recently, and some key was touched longest ago. The one touched longest ago is the LRU candidate.

So the core challenge is: how do you efficiently track that ordering, and how do you remove a key from it quickly when eviction happens?

The most natural first instinct is something like: *just stamp each key with a timestamp every time it's used, and when you need to evict, find the one with the oldest timestamp.* That's intuitive, and it works conceptually. It's exactly the kind of thinking that leads to a real solution — it's just not fast enough yet.

From there, the thought process naturally evolves: can we maintain an explicit ordering instead of scanning timestamps? That leads us toward a linked list. And once we see that removing from the middle of a list is slow, we start thinking about how to make that `O(1)` too — which leads us to a doubly linked list with direct node pointers.

Let's follow that progression.

---

## Approach 1: Aging the Keys

### Idea

The simplest implementation of "track how recently each key was used" is to assign an age to every key. Keep a global counter (`lastAge`) that increments on every operation. Every time a key is accessed or inserted, update its age to the current counter value.

When eviction is needed, scan all keys and find the one with the lowest age. That's your LRU candidate.

The data structures are simple:
- `caches`: a hash map from key to value
- `cacheAges`: a hash map from key to its last-used timestamp

Every `get` or `put` stamps the key with `lastAge++`, making sure the most recently used key always has the highest age value.

### Code

```cpp
class LRUCache {
    private:
    unordered_map<int, int> caches;
    unordered_map<int, int> cacheAges;
    int capacity;
    int lastAge;
public:
    LRUCache(int capacity) : capacity(capacity), lastAge(0) {}
    
    int get(int key) {
        auto it = caches.find(key);
        if (it != caches.end()) {
            cacheAges[key] = lastAge++;
            return it->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (caches.find(key) == caches.end() && caches.size() == capacity) {
            int LRUkey = caches.begin()->first;
            int LRUage = cacheAges[LRUkey];
            for (auto& p : caches) {
                if (cacheAges.at(p.first) < LRUage) {
                    LRUkey = p.first;
                    LRUage = cacheAges.at(LRUkey);
                }
            }
            caches.erase(caches.find(LRUkey));
            cacheAges.erase(cacheAges.find(LRUkey));
        }
        caches[key] = value;
        cacheAges[key] = lastAge++;
    }
};
```

### Complexity

- **Time:** `get` is `O(1)`. `put` is `O(N)` in the worst case because we scan all keys to find the minimum age.
- **Space:** `O(N)` for the two hash maps.

### Limitations

This approach is clean and easy to reason about, but it violates the `O(1)` requirement for `put`. Every eviction requires a full scan. With up to `2 * 10^5` operations, this adds up fast. We need a way to find the LRU key without scanning everything.

---

## Approach 2: Linked List for Ordering

### Idea

The key insight here: instead of storing ages and scanning for the minimum, why not *maintain the order explicitly*?

If we keep a list where the front is always the least recently used key and the back is always the most recently used, then:

- Eviction is just popping the front — `O(1)`.
- Marking a key as recently used means moving it to the back.

Every `get` or `put` removes the key from wherever it is in the list and appends it to the back. The front of the list is always your LRU candidate.

```
Least Recent  <-- [key_A, key_B, key_C, key_D] --> Most Recent
                   ^                               ^
                 evict from here              append here
```

### Code

```cpp
class LRUCache {
    private:
    unordered_map<int, int> caches;
    list<int> keys;
    int capacity;
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        auto it = caches.find(key);
        if (it != caches.end()) {
            keys.remove(key);
            keys.push_back(key);
            return it->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (caches.find(key) != caches.end()) {
            keys.remove(key);
        } else if (caches.size() == capacity) {
            int lru_key = keys.front();
            keys.pop_front();
            caches.erase(lru_key);
        }
        caches[key] = value;
        keys.push_back(key);
    }
};
```

### Complexity

- **Time:** Both `get` and `put` call `keys.remove(key)`, which is `O(N)` because `std::list::remove` scans the list to find the element.
- **Space:** `O(N)`.

### Limitations

Better conceptually, but `list::remove` is still `O(N)`. We're doing a linear scan to find the position of the key before we can move it. The ordering idea is right; the removal mechanism is the bottleneck.

To fix this, we need to jump directly to the node in the list without scanning. And for that, we need to store pointers.

---

## Approach 3: Doubly Linked List with Direct Node Pointers (Optimal)

### Idea

The "aha moment" here is this: if we store a pointer to the list node directly in the hash map, we can jump to any node in `O(1)` and unlink it in `O(1)` — no searching required.

We build a doubly linked list manually (rather than using `std::list`) so we have full control over node pointers. We use two sentinel nodes, `head` and `tail`, to avoid edge-case handling for empty lists or boundary insertions:

```
head <-> [node_A] <-> [node_B] <-> [node_C] <-> tail
          ^LRU                        ^MRU
```

- The hash map stores: `key -> Cache* (pointer to the node)`
- `push_back`: insert a node just before `tail`
- `unlink`: detach a node from its neighbors
- `move_to_back`: unlink then push_back (marks a key as recently used)

When evicting, the LRU node is always `head->next` — `O(1)` access. A nice optimization in the eviction path: instead of deleting the node and allocating a new one, we reuse the existing node by overwriting its key and value, then moving it to the back.

### Code

```cpp
class LRUCache {
    private:
    struct Cache {
        int key;
        int value;
        Cache* next;
        Cache* prev;
        Cache(int k, int v, Cache* p = nullptr, Cache* n = nullptr)
            : key(k), value(v), prev(p), next(n) {}
    };
    unordered_map<int, Cache*> caches;
    Cache* head;
    Cache* tail;
    int capacity;

    void unlink(Cache* cache) {
        cache->prev->next = cache->next;
        cache->next->prev = cache->prev;
    }

    void push_back(Cache* cache) {
        tail->prev->next = cache;
        cache->prev = tail->prev;
        cache->next = tail;
        tail->prev = cache;
    }

    void move_to_back(Cache* cache) {
        unlink(cache);
        push_back(cache);
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Cache(-1, -1);
        tail = new Cache(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Cache* cache = head;
        while (cache) {
            Cache* next = cache->next;
            delete cache;
            cache = next;
        }
    }

    int get(int key) {
        auto it = caches.find(key);
        if (it != caches.end()) {
            Cache* cache = it->second;
            move_to_back(cache);
            return cache->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (caches.find(key) != caches.end()) {
            Cache* cache = caches[key];
            cache->value = value;
            move_to_back(cache);
            caches[key] = cache;
        } else if (caches.size() == capacity) {
            Cache* lru_cache = head->next;
            caches.erase(lru_cache->key);
            lru_cache->key = key;
            lru_cache->value = value;
            move_to_back(lru_cache);
            caches[key] = lru_cache;
        } else {
            Cache* new_cache = new Cache(key, value);
            push_back(new_cache);
            caches[key] = new_cache;
        }
    }
};
```

### Complexity

- **Time:** Both `get` and `put` are `O(1)`. Hash map lookup is `O(1)`, and all linked list operations (unlink, push_back) are `O(1)` pointer manipulations.
- **Space:** `O(N)` for the hash map and the linked list nodes.

### Why it works

Every operation touches exactly one node. We go directly to it via the hash map, adjust at most four pointers to move it, and update one hash map entry. No scanning anywhere.

The sentinel nodes (`head` and `tail`) are a small but elegant trick. They eliminate every boundary check: there's never a "is this the first node?" or "is the list empty?" branch in the pointer logic. The list always has at least two nodes, so `unlink` and `push_back` are always safe to call.

---

## Key Takeaways

- **Hash map + doubly linked list** is the classic combo for `O(1)` ordered data structures. Whenever you need both fast lookup and fast ordered eviction, think of this pair.
- **Sentinel nodes** simplify linked list pointer logic significantly. Always worth adding a dummy head and tail to avoid edge cases.
- **Store pointers, not values** in the hash map when you need direct access to list nodes. This is what enables `O(1)` removal.
- **Reuse nodes on eviction** instead of delete + new. It's a minor optimization but avoids unnecessary allocations.
- The progression here is a good mental model: timestamps -> explicit ordering -> pointer-based ordering. Each step removes one bottleneck.

---

## References & Further Reading

**Related LeetCode Problems:**

- [460. LFU Cache](https://leetcode.com/problems/lfu-cache/) — The next level: evict by frequency, not recency
- [380. Insert Delete GetRandom `O(1)`](https://leetcode.com/problems/insert-delete-getrandom-o1/) — Similar "`O(1)` for everything" constraint
- [432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/) — Combines ordered eviction with frequency tracking

**Patterns & Concepts:**

- Doubly linked list with sentinel nodes
- Hash map + linked list (a recurring pattern in cache design problems)
- Amortized `O(1)` data structure design
- Memory management with manual node reuse
