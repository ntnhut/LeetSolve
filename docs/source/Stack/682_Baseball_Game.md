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
#include <vector>
#include <iostream>
#include <string>
#include <numeric>
using namespace std;
int calPoints(const vector<string>& ops) {
    vector<int> stk;
    for (auto& s : ops) {
        if (s == "C") {
            stk.pop_back();
        } else if (s == "D") {
            stk.push_back(stk.back()*2);
        } else if (s == "+") {
            stk.push_back(stk[stk.size() - 1] + stk[stk.size() - 2]);
        } else { // s is an integer
            stk.push_back(stoi(s));
        }
    }
    // compute the sum
    return accumulate(stk.begin(), stk.end(), 0);
}
int main() {
    vector<string> ops{"5","2","C","D","+"};
    cout << calPoints(ops) << endl;
    ops = {"5","-2","4","C","D","9","+","+"};
    cout << calPoints(ops) << endl;
}
```
```text
Output:
30
27
```
This solution simulates the baseball game by processing each round's operation and maintaining a stack of valid points. It accurately calculates the final sum of valid points based on the given operations. 

### Complexity
* Runtime: `O(N)`, where `N = ops.length`.
* Extra space: `O(N)`.

## Implementation tips

1. The data structure `stk` you might need to solve this problem is a stack. But here are the reasons you had better use `std::vector`:
    * `std::vector` has also methods `push_back(value)` and `pop_back()` like the ones in stack.
    * On the other hand, a stack does not give easy access to the second last element for the operator `"+"` in this problem.

2. [`accumulate(stk.begin(), stk.end(), 0)`](https://en.cppreference.com/w/cpp/algorithm/accumulate) computes the sum of the vector `stk`.


## Exercise
- [Crawler Log Folder](https://leetcode.com/problems/crawler-log-folder/).




