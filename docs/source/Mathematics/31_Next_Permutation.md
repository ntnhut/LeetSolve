# 31. Next Permutation

## Problem Statement

A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for `arr = [1,2,3]`, the following are all the permutations of `arr`: `[1,2,3]`, `[1,3,2]`, `[2,1,3]`, `[2,3,1]`, `[3,1,2]`, `[3,2,1]`.

The **next permutation** of an array of integers is the next lexicographically greater permutation of its integers. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

- The next permutation of `arr = [1,2,3]` is `[1,3,2]`.
- The next permutation of `arr = [2,3,1]` is `[3,1,2]`.
- The next permutation of `arr = [3,2,1]` is `[1,2,3]`, because `[3,2,1]` does not have a lexicographically larger rearrangement.

Given an array of integers `nums`, find the next permutation of `nums`. The replacement must be in place and use only constant extra memory.

### Examples

```
Input: nums = [1,2,3]   Output: [1,3,2]
Input: nums = [3,2,1]   Output: [1,2,3]
Input: nums = [1,1,5]   Output: [1,5,1]
```

### Constraints
- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 100`

---

## First Intuition

The moment you read "next permutation," your first instinct might be: generate all permutations, sort them, and return the one that comes right after the current arrangement. It's the most literal interpretation of the problem, and it makes sense as a starting point.

But that path collapses quickly. The number of permutations of an array of length `n` is `n!`. Even for `n = 10`, that's 3,628,800 permutations to generate, sort, and search through. For the given constraints (`n <= 100`), this is astronomically slow. So the brute-force approach is off the table.

The right move here is to step back and think about what "next permutation" actually means structurally, not algorithmically. Can we derive the answer directly from the current array, without generating anything else?

Let's think about how a dictionary is built. If you're listing words in alphabetical order, you change the *last* letter first, then the second-to-last, and so on. The same principle applies to permutations. To get the "next" arrangement, you want to make the smallest possible change that still makes the array lexicographically larger.

That means: touch as few digits from the left as possible, and when you do change something, make it the smallest increase you can.

Starting from this mental model is what unlocks the efficient solution.

---

## Approach: In-Place Next Permutation

### Idea

Let's build up the algorithm by reasoning through examples carefully.

**The simple case:**

Consider `[1, 2, 3]`. The suffix `[2, 3]` is in ascending order. To get the next permutation, we just swap the last two elements: `[1, 3, 2]`. Easy.

**The decreasing suffix:**

Now consider `[3, 2, 1]`. This is the largest possible permutation. No matter how you rearrange the suffix, you can't make it larger. The answer wraps around to `[1, 2, 3]`, the smallest permutation. This is the "reverse everything" edge case.

**The general case:**

Now the interesting one: `[1, 3, 2]`. What's the next permutation?

Think of it this way. Starting from the right, we ask: is there a position where the element is *smaller* than the one to its right? That position is a candidate for a "promotion." At index 0, we have `1`, and `1 < 3`, so yes.

But actually, let's scan from the right more carefully. Index 1 has `3`, and `3 > 2`, so it's not a promotion point. Index 0 has `1`, and `1 < 3`, so index 0 is our leftmost pivot.

Now, the suffix to the right of the pivot (`[3, 2]`) is in descending order. Why? Because we found the pivot by walking right-to-left until the sequence stopped decreasing. Everything to the right is already the *largest* it can be in that suffix.

To get the next permutation:
1. Find the pivot: the rightmost index `i` where `nums[i] < nums[i+1]`.
2. Find `b`: the smallest element in the suffix that is still greater than `nums[i]`. Since the suffix is descending, this is the rightmost element in the suffix that's greater than `nums[i]`.
3. Swap `nums[i]` and `b`. The suffix is still descending after the swap.
4. Reverse the suffix. This gives you the smallest possible arrangement of that suffix, which combined with the promoted pivot, gives the next permutation overall.

Let's trace through `[1, 3, 2]`:

```
[1, 3, 2]
 ^        <- pivot at index 0, nums[0]=1 < nums[1]=3

suffix = [3, 2] (descending)
find rightmost element > 1 in suffix: that's 2, at index 2

swap nums[0] and nums[2]: [2, 3, 1]
reverse suffix starting at index 1: [2, 1, 3]
```

Result: `[2, 1, 3]`. Correct.

This works because:
- Swapping the pivot with the just-right element makes the prefix larger by the minimum necessary amount.
- Reversing the suffix (which is descending after the swap) turns it into ascending order, the smallest possible arrangement of those elements.

The two cases (simple and edge) are naturally handled:
- If `c < d` in `[a, b, c, d]` (like `[1, 2, 3]`), the pivot is at the second-to-last position and the swap + reverse resolves to a simple swap of the last two.
- If no pivot is found, the entire array is descending (maximum permutation), and reversing the whole thing gives the minimum.

### Code

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() == 1) return;

        // Step 1: Find the pivot (rightmost index where nums[i] < nums[i+1])
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i+1]) {
            i--;
        }

        // Step 2: If pivot exists, find the element just greater than nums[i]
        if (i >= 0) {
            int j = i + 1;
            while (j < nums.size() && nums[j] > nums[i]) {
                j++;
            }
            // nums[j-1] is the rightmost element greater than nums[i]
            swap(nums, i, j - 1);
        }

        // Step 3: Reverse the suffix
        reverse(nums.begin() + i + 1, nums.end());
    }

    void swap(vector<int>& nums, int i, int j) {
        int t = nums[i];
        nums[i] = nums[j];
        nums[j] = t;
    }
};
```

### Complexity

**Time complexity: `O(N)`**

We make at most two passes through the array: one to find the pivot (right to left), and one to find the swap target. The reverse at the end is also `O(N)` in the worst case. All operations are linear.

**Space complexity: `O(1)`**

Everything is done in place. No extra memory is allocated beyond a few index variables.

### Key Insight

The critical observation is that the suffix to the right of the pivot is always in descending order by construction. This means:
- Finding the swap target is a simple linear scan (no need for binary search or sorting).
- After the swap, reversing that descending suffix in `O(N)` gives the smallest possible arrangement, which is exactly what we want.

---

## Key Takeaways

- **Think structurally, not generatively.** The brute-force instinct (generate all permutations) is almost always wrong for permutation problems. Ask instead: what structural property characterizes the answer?

- **The descending suffix pattern.** Whenever you see a "next greater arrangement" type of problem, scan from the right. The first position where the sequence breaks from descending to ascending is your pivot.

- **Pivot + swap + reverse** is a classic pattern. Recognizing it here helps you solve similar problems: find the rightmost breakpoint, promote the smallest possible element, and minimize the rest.

- **In-place constraints push you toward smarter algorithms.** The `O(1)` space requirement here rules out sorting or copying, which forces you to reason about the array's structure directly.

- **Edge cases to remember:**
  - Entirely descending array: no pivot found, reverse everything.
  - Single element: trivially return.
  - Duplicate elements: the `>=` in the pivot-finding condition handles this correctly (we skip equal elements when searching left).

---

## References & Further Reading

### Related LeetCode problems

- [46. Permutations](https://leetcode.com/problems/permutations/): Generate all permutations; good for understanding the enumeration approach.
- [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/): Find the k-th permutation directly; related lexicographic reasoning.
- [556. Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/): Essentially the same algorithm applied to digits of an integer.
- [321. Create Maximum Number](https://leetcode.com/problems/create-maximum-number/): Greedy construction of lexicographically largest numbers.

### Patterns and concepts

- Lexicographic ordering of sequences
- Two-pointer / in-place reversal
- Greedy: make the smallest change possible to advance to the next state