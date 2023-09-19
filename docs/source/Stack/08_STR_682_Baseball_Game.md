# Baseball Game

## [Problem statement](https://leetcode.com/problems/baseball-game/)

You are responsible for keeping score in a unique baseball game with special rules. The game involves multiple rounds where the scores of previous rounds can influence the scores of future rounds.

At the beginning of the game, your record is empty. You are given a list of operations called `ops`, where each `ops[i]` is one of the following:

1. An integer `x` - This represents recording a new score of `x`.
2. `"+"` - This represents recording a new score that is the sum of the previous two scores. It is guaranteed that there will always be two previous scores.
3. `"D"` - This represents recording a new score that is double the previous score. It is guaranteed that there will always be a previous score.
4. `"C"` - This represents invalidating the previous score, removing it from the record. It is guaranteed that there will always be a previous score.

Your task is to calculate and return the sum of all the scores in the record after performing all the operations. 

### Example 1
```text
Input: ops = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record; the record is now [5].
"2" - Add 2 to the record; the record is now [5, 2].
"C" - Invalidate and remove the previous score; the record is now [5].
"D" - Add 2 * 5 = 10 to the record; the record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.
```

### Example 2
```text
Input: ops = ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation:
"5" - Add 5 to the record; the record is now [5].
"-2" - Add -2 to the record; the record is now [5, -2].
"4" - Add 4 to the record; the record is now [5, -2, 4].
"C" - Invalidate and remove the previous score; the record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record; the record is now [5, -2, -4].
"9" - Add 9 to the record; the record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.
```

### Example 3
```text
Input: ops = ["1"]
Output: 1
``` 

### Constraints

* `1 <= ops.length <= 1000`.
* `ops[i]` is `"C"`, `"D"`, `"+"`, or a string representing an integer in the range `[-3 * 10^4, 3 * 10^4]`.
* For operation `"+"`, there will always be at least two previous scores on the record.
* For operations `"C"` and `"D"`, there will always be at least one previous score on the record.

## Solution

### Code
```cpp
int calPoints(vector<string>& ops) {
    vector<int> stk;
    for (string& s : ops) {
        if (s == "C") {
            stk.pop_back();
        } else if (s == "D") {
            stk.push_back(stk.back()*2);
        } else if (s == "+") {
            stk.push_back(stk[stk.size() - 1] + stk[stk.size() - 2]);
        } else {
            stk.push_back(stoi(s));
        }
    }
    return accumulate(stk.begin(), stk.end(), 0);
}
```

### Code explanation

1. The code uses a stack data structure, represented by the `vector<int> stk`, to keep track of the points earned in each round.

2. The code iterates through each operation in the `ops` vector.

   - If the current operation is `"C"` (cancel), the code pops the last valid round's score from the stack. This effectively removes the most recent round's score.

   - If the current operation is `"D"` (double), the code calculates the score for the current round by doubling the score of the previous round. It pushes this doubled score onto the stack.

   - If the current operation is `"+"` (addition), the code calculates the score for the current round by adding the scores of the last two valid rounds. It pushes this sum onto the stack.

   - If the current operation is not `"C"`, `"D"`, or `"+"`, it is assumed to be a valid integer string representing the score of a round. The code converts this string to an integer using `stoi(s)` and pushes the integer score onto the stack.

3. After processing all the operations, the code calculates the final sum of valid points by using the `accumulate` function. It sums all the elements in the `stk` vector, starting from the beginning (0 as the initial sum). The code returns the final sum as the result.

In summary, this code simulates the baseball game by processing each round's operation and maintaining a stack of valid points. It accurately calculates the final sum of valid points based on the given operations. 

### Complexity
* Runtime: `O(N)`, where `N = ops.length`.
* Extra space: `O(N)`.

```{admonition} Implementation tips
:class: tip

1. The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use [`std::vector`](https://en.cppreference.com/w/cpp/container/vector):
    * `std::vector` has also methods [`push_back(value)`](https://en.cppreference.com/w/cpp/container/vector/push_back) and [`pop_back()`](https://en.cppreference.com/w/cpp/container/vector/pop_back) like the ones in stack.
    * On the other hand, a stack does not give easy access to the second last element for the operator `"+"` in this problem.

2. [`accumulate(stk.begin(), stk.end(), 0)`](https://en.cppreference.com/w/cpp/algorithm/accumulate) computes the sum of the vector `stk`.

```
