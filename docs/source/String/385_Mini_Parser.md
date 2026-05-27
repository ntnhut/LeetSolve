# 385. Mini Parser

## Problem Statement

Given a string `s` representing the serialization of a nested list, implement a parser to deserialize it and return the deserialized `NestedInteger`.

Each element is either an integer or a list whose elements may also be integers or other lists.

```
Example 1:
Input: s = "324"
Output: 324
Explanation: Return a NestedInteger object containing a single integer 324.

Example 2:
Input: s = "[123,[456,[789]]]"
Output: [123,[456,[789]]]
Explanation: Return a NestedInteger object containing a nested list with 2 elements:
  1. An integer containing value 123.
  2. A nested list containing two elements:
       i.  An integer containing value 456.
       ii. A nested list with one element:
             a. An integer containing value 789.
```

### Constraints

- `1 <= s.length <= 5 * 10^4`
- `s` consists of digits, square brackets `[]`, negative sign `-`, and commas `,`.
- `s` is the serialization of a valid `NestedInteger`.
- All values are in the range `[-10^6, 10^6]`.

The `NestedInteger` interface you're given looks like this:

```cpp
class NestedInteger {
  public:
    NestedInteger();               // empty nested list
    NestedInteger(int value);      // single integer

    bool isInteger() const;
    int getInteger() const;
    void setInteger(int value);
    void add(const NestedInteger &ni);
    const vector<NestedInteger> &getList() const;
};
```

---

## First Intuition

The first thing to notice is that the structure of this string is recursive. A `NestedInteger` is either a plain integer like `"324"`, or a bracketed list like `"[123,[456,[789]]]"` where each comma-separated element is itself a `NestedInteger`.

That observation almost writes the solution for you. If the string doesn't start with `[`, it's a plain integer: just parse it and return. If it does start with `[`, strip the outer brackets and split on commas, then recursively parse each piece.

The catch is that splitting on commas naively doesn't work. In `"[123,[456,[789]]]"`, the comma between `123` and `[456,[789]]` is a top-level separator, but the comma between `456` and `[789]` is nested one level deep. You can't split on every comma. You need to split only on the commas that sit at depth zero, i.e., not inside any brackets.

Tracking bracket depth with a counter solves that cleanly. Every `[` increments the counter, every `]` decrements it, and you only treat a comma as a separator when the counter is zero. This is a well-worn pattern for balanced-bracket parsing and it's the foundation of both approaches here.

---

## Approach 1: Recursive with `substr`

### Idea

The recursive structure of the problem maps naturally to a recursive function. The base case is a plain integer string (no leading `[`), handled with `stoi`. The recursive case strips the outer brackets, then scans character by character to find top-level comma separators.

When the depth counter hits zero at a comma, you've found a boundary. Extract the substring from the last boundary to this comma, recurse on it, and add the result to the current `NestedInteger`. After the loop, don't forget to handle the last segment, which has no trailing comma to trigger the extraction.

```cpp
class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) return NestedInteger();
        if (s[0] != '[') return NestedInteger(stoi(s));

        NestedInteger result;
        assert(s[0] == '[' && s[s.length()-1] == ']');
        int start = 1;
        int openb = 0;
        for (int i = start; i < s.length() - 1; i++) {
            if (s[i] == '[') openb++;
            else if (s[i] == ']') openb--;
            else if (s[i] == ',' && openb == 0) {
                result.add(deserialize(s.substr(start, i - start)));
                start = i + 1;
            }
        }
        if (start < s.length() - 1)
            result.add(deserialize(s.substr(start, s.length() - 1 - start)));
        return result;
    }
};
```

### Complexity

- **Time:** `O(N^2)` in the worst case. Each recursive call invokes `substr`, which copies a portion of the string. For a deeply nested input, you end up copying substrings at every level of recursion, and the total work adds up to quadratic.
- **Space:** `O(N)` for the recursion stack and the string copies.

### Limitations

The logic is correct, but `substr` is the bottleneck. Every time you recurse, you're allocating and copying a new string. For large inputs or deeply nested structures, this gets expensive fast.

The fix is to stop copying. If you can pass a view into the original string rather than a new copy, you get the same recursive structure with `O(1)` substring operations.

---

## Approach 2: Recursive with `string_view`

### Idea

`std::string_view` is a non-owning reference to a portion of a string. Calling `.substr()` on a `string_view` doesn't allocate anything, it just adjusts a pointer and a length. Swapping `string` for `string_view` throughout makes the recursive structure identical to before, but without any copying.

The only other change worth noting is the integer parsing. `std::stoi` requires a `std::string`, so passing a `string_view` directly would force a conversion and defeat the purpose. `std::from_chars` is the right tool here: it works directly on a character range, no allocation needed.

```cpp
int strvtoi(string_view s) {
    int result;
    std::from_chars(s.data(), s.data() + s.size(), result);
    return result;
}

class Solution {
    NestedInteger parse(string_view s) {
        if (s.empty()) return NestedInteger();
        if (s[0] != '[') return NestedInteger(strvtoi(s));

        NestedInteger result;
        size_t start = 1;
        int openb = 0;
        for (int i = start; i < s.length(); i++) {
            if (s[i] == '[') openb++;
            else if (s[i] == ']') openb--;
            else if (s[i] == ',' && openb == 0) {
                result.add(parse(s.substr(start, i - start)));
                start = i + 1;
            }
        }
        if (start < s.length() - 1)
            result.add(parse(s.substr(start, s.length() - 1 - start)));
        return result;
    }

public:
    NestedInteger deserialize(const string& s) {
        return parse(s);
    }
};
```

### Complexity

- **Time:** `O(N)`. Each character is visited a constant number of times across all levels of recursion. `string_view::substr` is `O(1)`, so there's no hidden linear cost per call anymore.
- **Space:** `O(D)` for the recursion stack, where `D` is the maximum nesting depth. In the worst case this is `O(N)`, but for typical inputs it's much smaller. No extra heap allocations for string copies.

### Why This Works

The recursive structure is unchanged. The only difference is that instead of handing each recursive call a freshly allocated copy of a substring, you hand it a lightweight view into the original buffer. The `string_view::substr` call just moves a pointer, so the "copying" cost that made Approach 1 quadratic is gone entirely.

---

## Key Takeaways

- **Bracket depth tracking** is the standard technique for finding top-level delimiters in nested string formats. Increment on `[`, decrement on `]`, act only at depth zero.
- **`string_view` is a drop-in optimization** for recursive string parsing. If your algorithm passes substrings around recursively and `substr` is the bottleneck, switching from `std::string` to `std::string_view` is often all it takes to go from `O(N^2)` to `O(N)`.
- **`std::from_chars` pairs naturally with `string_view`**. It works on raw character ranges with no allocation, which is exactly what you want when avoiding copies.
- **Recursive structure mirrors problem structure.** When a problem is defined recursively (nested lists, nested expressions, tree-shaped input), a recursive parser is often the clearest and most natural solution.
- Watch out for the **off-by-one in the final segment**. After the loop ends, there's always a last element between `start` and the closing `]` that never triggered a comma. Don't forget to add it.

---

## References and Further Reading

- [LeetCode 385. Mini Parser](https://leetcode.com/problems/mini-parser/)

### Related LeetCode Problems

- [394. Decode String](https://leetcode.com/problems/decode-string/): Bracket-balanced parsing with repetition counts, same depth-tracking pattern
- [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/): Recursive parsing of a structured string with nested groups
- [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/): Works with the same `NestedInteger` interface

### Patterns Used

- Bracket depth counting for top-level delimiter detection
- Recursive descent parsing on structured strings
- Non-owning string views for zero-copy substring operations

### Concepts Worth Reviewing

- `std::string_view` and why it avoids allocation
- `std::from_chars` as an allocation-free alternative to `stoi`
- How recursive parsing relates to formal grammars (this problem's input follows a simple context-free grammar)