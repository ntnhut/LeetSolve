# 1641. Count Sorted Vowel Strings

## Problem Statement

Given an integer `n`, return the number of strings of length `n` that consist only of vowels (`a`, `e`, `i`, `o`, `u`) and are lexicographically sorted.

A string `s` is lexicographically sorted if for all valid `i`, `s[i]` is the same as or comes before `s[i + 1]` in the alphabet.

### Example 1

```text
Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
```

### Example 2

```text
Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
```

### Example 3

```text
Input: n = 33
Output: 66045
```

### Constraints

- `1 <= n <= 50`

---

## First Intuition

The sorted-order requirement means that once a string advances to a later vowel, it can never return to an earlier one. A valid string is made of a run of `a`s, then a run of `e`s, then `i`s, `o`s, and `u`s. Some runs can be empty.

One natural approach is to count valid strings by their first vowel. A string starting with `u` has only one possibility: every character must be `u`. A string starting with `o` can use `o` and `u`; one starting with `i` can use `i`, `o`, and `u`, and so on. These groups build on each other, which hints at a recurrence we can calculate from shorter strings.

There is also a second way to look at the same structure. Since each vowel appears in one contiguous block, a string is fully described by the number of times each vowel appears. That observation leads to a direct combinatorial formula.

---

## Approach 1: Dynamic Programming

### Idea

Let `S(v, n)` be the number of valid strings of length `n` that start with vowel `v`.

For `v` other than `u`, a length-`n` string starting with `v` either has another `v` next, or moves to a later vowel. The first group corresponds to `S(v, n - 1)`. The later-vowel group corresponds to `S(next(v), n)`. Therefore:

```text
S(v, n) = S(v, n - 1) + S(next(v), n)
```

For length one, each vowel contributes one string: `S(v, 1) = 1`. For every length, `S(u, n) = 1`.

We need the sum of the counts for all five starting vowels. The code stores those counts in five variables and updates from right to left, so each value can use the newly computed count to its right.

### Code

```cpp
#include <iostream>
using namespace std;

int countVowelStrings(int n) {
    int a = 1;
    int e = 1;
    int i = 1;
    int o = 1;
    int u = 1;

    while (n > 1) {
        o += u;
        i += o;
        e += i;
        a += e;
        n--;
    }

    return a + e + i + o + u;
}

int main() {
    cout << countVowelStrings(1) << endl;
    cout << countVowelStrings(2) << endl;
    cout << countVowelStrings(33) << endl;
}
```

```text
Output:
5
15
66045
```

### Complexity

- **Time:** `O(n)`, with one iteration per string length.
- **Space:** `O(1)`, since only five counts are stored.

### Limitations

This solution is efficient, but it still iterates through all lengths up to `n`. The recurrence does not immediately show why the answer can be computed with a fixed number of arithmetic operations. For that, count the possible vowel frequencies directly.

---

## Approach 2: Combinatorics with Stars and Bars

### Idea

Let `a`, `e`, `i`, `o`, and `u` be the number of appearances of each vowel. Since the string has length `n`, these are nonnegative integers satisfying:

```text
a + e + i + o + u = n
```

Each choice of counts corresponds to exactly one sorted string. For example, `(2, 0, 1, 0, 0)` represents `"aai"`.

We now need to count the nonnegative integer solutions to an equation with five variables. Stars and bars represents the `n` vowel occurrences as stars and separates the five groups with four bars:

```text
**| |*||
```

Bars can be adjacent or appear at either end. Those cases represent vowels with zero occurrences. There are `n + 4` total positions, and choosing four positions for the bars gives:

```text
C(n + 4, 4)
```

Using the binomial coefficient formula:

```text
C(n + 4, 4) = (n + 4)! / (4! * n!)
            = (n + 1)(n + 2)(n + 3)(n + 4) / 24
```

### Code

```cpp
#include <iostream>
using namespace std;

int countVowelStrings(int n) {
    return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
}

int main() {
    cout << countVowelStrings(1) << endl;
    cout << countVowelStrings(2) << endl;
    cout << countVowelStrings(33) << endl;
}
```

```text
Output:
5
15
66045
```

### Complexity

- **Time:** `O(1)`, since the formula uses a fixed number of operations.
- **Space:** `O(1)`.

### Why This Works

Sorted order fixes where each vowel's group appears. We only need to choose the size of each group. Stars and bars counts exactly the ways to split `n` occurrences among five groups, including empty groups.

---

## Key Takeaways

- A nondecreasing sequence over a small ordered alphabet can often be described by the frequency of each value.
- Dynamic programming can reveal a counting pattern, while combinatorics may provide a direct formula for the same count.
- Stars and bars applies to nonnegative counts, so empty groups must be included.

---

## References and Further Reading

- [LeetCode 1641. Count Sorted Vowel Strings](https://leetcode.com/problems/count-sorted-vowel-strings/)

### Related LeetCode Problems

- [62. Unique Paths](https://leetcode.com/problems/unique-paths/): Counts paths using a binomial coefficient.
- [118. Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/): Builds binomial coefficients used in combinations.

### Patterns Used

- Dynamic programming with rolling state
- Stars and bars
- Combinations and binomial coefficients
