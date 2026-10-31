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

The sorted-order requirement is restrictive, but it also gives us a useful structure: once a string moves from one vowel to a later vowel, it can never move back. Every valid string is therefore made of some number of `a`s, followed by some number of `e`s, then `i`s, `o`s, and `u`s.

For example, a length-three string might be `"aai"` or `"ouu"`. It cannot be `"eai"`, because the letters move backward from `e` to `a`.

A natural first step is to count strings by their first vowel. Strings starting with `u` are easy: there is only `"uuu..."`. Strings starting with `o` can use only `o` and `u`, while strings starting with `i` can use `i`, `o`, and `u`. This suggests a recurrence: count the strings that continue with the same first vowel, then add the strings whose next vowel is the first letter instead.

We can compute those counts from the smallest length upward and keep only a few running totals. That gives a compact dynamic-programming solution. Before settling for iteration, though, the block structure of each string also suggests a direct combinatorial count.

---

## Approach 1: Dynamic Programming

### Idea

Let `S(v, n)` be the number of valid strings of length `n` that start with vowel `v`.

For a vowel other than `u`, a valid string starting with `v` has two possibilities after its first character:

1. The rest of the string starts with `v` too.
2. The rest starts with a vowel later than `v`.

The second case can be counted as `S(next(v), n)`: a length-`n` string starting with the next vowel corresponds to a length-`n - 1` suffix that starts with that vowel or anything after it. Thus:

```text
S(v, n) = S(v, n - 1) + S(next(v), n)
```

The smallest case is `S(v, 1) = 1` for every vowel. Also, `S(u, n) = 1` for every `n`, since a string starting with `u` can contain only `u`s.

We need the sum of the counts for all five starting vowels. Instead of storing a table for every length, we update five variables in place. Each update uses the value for the vowel immediately to its right, so we process from `u` toward `a`.

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

- **Time:** `O(n)`, because each iteration advances the string length by one.
- **Space:** `O(1)`, since the algorithm keeps only five counts.

### Limitations

This solution is already efficient and uses constant space, but it still performs `n - 1` iterations. The recurrence also hides a simpler counting interpretation: instead of building counts by length, we can count how many ways there are to distribute the characters among the five vowels.

---

## Approach 2: Combinatorics with Stars and Bars

### Idea

Every sorted string is determined by how many times each vowel appears. Let those counts be `a`, `e`, `i`, `o`, and `u`. They are nonnegative integers satisfying:

```text
a + e + i + o + u = n
```

For instance, the counts `(2, 0, 1, 0, 0)` represent `"aai"`. This is a one-to-one mapping: each choice of five counts gives exactly one sorted string, and every sorted string gives one choice of counts.

So the problem becomes counting the nonnegative integer solutions to an equation with five variables. The stars-and-bars method represents the `n` vowel occurrences as stars and separates the five groups with four bars:

```text
**| |*||
```

Adjacent bars and bars at either end are allowed. They represent vowels that do not appear in the string.

There are `n + 4` total positions for the stars and bars. Choosing which four positions contain the bars gives:

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

- **Time:** `O(1)`, since the formula uses a fixed number of arithmetic operations.
- **Space:** `O(1)`, since it uses no additional storage.

### Why This Works

The sorted order means the positions of all occurrences of each vowel are fixed once their counts are known. We do not need to choose an ordering for the characters; we only need to choose five nonnegative counts that add up to `n`.

The stars-and-bars formula counts exactly those choices. With `n <= 50`, the intermediate product and final answer both fit in a 32-bit signed integer.

---

## Key Takeaways

- When a sequence must stay in sorted order, try describing it by the counts of each distinct value.
- A sorted vowel string is uniquely determined by five nonnegative counts whose sum is `n`.
- Stars and bars counts ways to distribute identical items among groups when groups may be empty.
- Dynamic programming is useful when a recurrence is easy to derive; look for a direct counting argument when the state has a simple combinatorial interpretation.
- In stars-and-bars problems, remember that zero-count groups are allowed. Consecutive bars and bars at the ends represent those empty groups.

---

## References and Further Reading

- [LeetCode 1641. Count Sorted Vowel Strings](https://leetcode.com/problems/count-sorted-vowel-strings/)

### Related LeetCode Problems

- [62. Unique Paths](https://leetcode.com/problems/unique-paths/): Counts paths using a binomial coefficient.
- [118. Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/): Builds binomial coefficients that appear in combinations.

### Patterns Used

- Dynamic programming with rolling state
- Stars and bars
- Combinations and binomial coefficients
