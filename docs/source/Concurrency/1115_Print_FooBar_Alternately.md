# 1115. Print FooBar Alternately

## Problem Statement

Suppose you are given the following code:

```cpp
class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
```

The same instance of `FooBar` will be passed to two different threads:

- thread A will call `foo()`, while
- thread B will call `bar()`.

Modify the given program to output `"foobar"` n times.

### Example 1
```
Input: n = 1
Output: "foobar"
```

### Example 2
```
Input: n = 2
Output: "foobarfoobar"
```

### Constraints
* `1 <= n <= 1000`

---

## First Intuition

When you first see this problem, the setup feels familiar. Two threads, one shared object, some output that needs to come out in a specific order. Your brain immediately jumps to the classic tool for protecting shared data: a mutex.

So the natural first sketch looks something like this: keep a boolean flag `fooTurn`, lock the mutex before checking it, and only print if it is your turn.

```cpp
void foo(function<void()> printFoo) {
  for (int i = 0; i < n; i++) {
    unique_lock<mutex> l(m);
    if (fooTurn) {
      printFoo();
      fooTurn = false;
    }
  }
}

void bar(function<void()> printBar) {
  for (int i = 0; i < n; i++) {
    unique_lock<mutex> l(m);
    if (!fooTurn) {
      printBar();
      fooTurn = true;
    }
  }
}
```

It looks reasonable. The mutex protects `fooTurn`, so reads and writes are safe. But there is a subtle and fatal flaw here.

The `if` branch does not wait. If `foo` gets scheduled and `fooTurn` happens to be `false` at that moment, it just skips the iteration entirely. The loop counter still advances. That thread has now wasted one of its `n` turns doing nothing.

Imagine `n = 3` and the scheduler decides to run `foo` three times in a row before `bar` gets a chance. All three iterations of `foo` might fire when `fooTurn` is false, and the output ends up shorter than expected or completely wrong.

The root issue here is that **mutual exclusion and turn-based waiting are two different problems.** A mutex solves the first. It does nothing for the second.

What we actually need is a way for a thread to say: "this is not my turn yet, put me to sleep and wake me up when the situation changes." That is precisely what `condition_variable` is designed for.

---

## Approach 1: Condition Variable

### Idea

A `condition_variable` lets a thread sleep inside a lock and wake up only when a predicate becomes true. This is the exact pattern we need:

1. Lock the shared state.
2. If it is not my turn, sleep and release the lock atomically.
3. Get woken up when the other thread signals a change.
4. Re-check the condition (to handle spurious wakeups).
5. Do the work, flip the flag, and notify the other thread.

The key call is `cv.wait(lock, predicate)`. It does not just check once. It atomically releases the lock, parks the thread, and when woken, re-acquires the lock and checks the predicate again before proceeding. This handles spurious wakeups transparently.

### Code

```cpp
class FooBar {
private:
  int n;
  bool fooTurn = true;
  mutex m;
  condition_variable cv;

public:
  FooBar(int n) : n(n) {}

  void foo(function<void()> printFoo) {
    for (int i = 0; i < n; i++) {
      {
        unique_lock<mutex> l(m);
        cv.wait(l, [this]{ return fooTurn; });
        printFoo();
        fooTurn = false;
      }
      cv.notify_one();
    }
  }

  void bar(function<void()> printBar) {
    for (int i = 0; i < n; i++) {
      {
        unique_lock<mutex> l(m);
        cv.wait(l, [this]{ return !fooTurn; });
        printBar();
        fooTurn = true;
      }
      cv.notify_one();
    }
  }
};
```

A few design details worth noting:

- `fooTurn = true` means `foo` gets the first turn by default.
- The inner braces around the `unique_lock` scope ensure the lock is released before `notify_one()` is called. This is good practice. Notifying while still holding the lock works, but it can cause the woken thread to immediately block again waiting to re-acquire the lock. Releasing first gives the other thread a cleaner path to run.
- Each thread flips `fooTurn` after printing, then notifies. The other side wakes up, checks its predicate, and proceeds.

### Complexity

- Time: `O(n)` prints per function, `O(n)` total synchronization steps.
- Space: `O(1)` extra.

### Limitation

The condition variable approach is correct and efficient, but it requires a bit of ceremony: a mutex, a flag, a condition variable, and a predicate. For a problem that is fundamentally about handing off a token between two threads, there is a cleaner mental model available.

---

## Approach 2: Semaphore (C++20)

### Idea

Step back and think about the problem in terms of *permits* rather than predicates.

- `foo` should be allowed to run first. Give it one permit upfront.
- `bar` should be blocked initially. Give it zero permits.
- After `foo` prints, it hands one permit to `bar`.
- After `bar` prints, it hands one permit back to `foo`.

This is a strict token handoff: `foo -> bar -> foo -> bar -> ...`

That mental model maps directly onto a semaphore. A semaphore holds a count of available permits. `acquire()` blocks until a permit is available and then consumes it. `release()` adds a permit and wakes a waiting thread.

No explicit mutex needed. No predicate. No flag. The semaphore counts are the entire shared state.

### Code

```cpp
#include <functional>
#include <semaphore>
using namespace std;

class FooBar {
private:
  int n;
  binary_semaphore fooSem{1}; // foo goes first
  binary_semaphore barSem{0}; // bar must wait

public:
  FooBar(int n) : n(n) {}

  void foo(function<void()> printFoo) {
    for (int i = 0; i < n; i++) {
      fooSem.acquire();
      printFoo();
      barSem.release();
    }
  }

  void bar(function<void()> printBar) {
    for (int i = 0; i < n; i++) {
      barSem.acquire();
      printBar();
      fooSem.release();
    }
  }
};
```

The structure here is almost elegant in its simplicity. Each method is three lines: acquire your permit, do the work, release the other thread's permit. The alternation is enforced by the semaphore counts alone.

`binary_semaphore` is used here because the count never needs to exceed 1. Exactly one thread holds the token at any given time.

Note that `binary_semaphore` requires C++20 and the `<semaphore>` header. If your environment does not support it, the condition variable approach is the right fallback.

### Complexity

- Time: `O(n)` per method.
- Space: `O(1)` extra.

---

## Key Takeaways

### Mutual exclusion and ordering are different problems
A mutex prevents data races. It does not enforce which thread runs next. Confusing the two is a very common mistake in early concurrency work.

### The `if` approach fails silently
Threads skip iterations instead of waiting, which leads to output that is shorter than expected with no crash or error to signal the bug.

### `condition_variable` is the right tool when a thread needs to wait on a changing predicate
The `wait(lock, predicate)` overload handles spurious wakeups automatically and is almost always what you want.

### Semaphore is the right tool for token handoff
When the problem is "thread A runs, then thread B runs, then thread A again," semaphores express that intent more directly than a flag plus a condition variable.

### Notify after releasing the lock
It is not strictly required, but it reduces unnecessary contention and is generally considered good practice.

---

## References and Further Reading

### Related LeetCode Problems

- [1114. Print in Order](https://leetcode.com/problems/print-in-order/) -- simpler version, three threads in fixed sequence
- [1116. Print Zero Even Odd](https://leetcode.com/problems/print-zero-even-odd/) -- three-thread coordination with similar techniques
- [1117. Building H2O](https://leetcode.com/problems/building-h2o/) -- semaphore-heavy problem with more complex ratios

### Concepts to Explore

- `std::condition_variable` -- [cppreference](https://en.cppreference.com/w/cpp/thread/condition_variable)
- `std::semaphore` (C++20) -- [cppreference](https://en.cppreference.com/w/cpp/thread/counting_semaphore)
- Spurious wakeups and why predicates matter
- The monitor pattern in concurrent programming