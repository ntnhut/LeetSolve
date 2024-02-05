# Remove Covered Intervals

## [Problem statement](https://leetcode.com/problems/remove-covered-intervals/)

You're given an array called `intervals`, where each element `intervals[i]` is a pair `[li, ri]` representing a half-open interval `[li, ri)`.

Your task is to remove all intervals from the list that are completely covered by another interval. An interval `[a, b)` is considered covered by the interval `[c, d)` if and only if `c` is less than or equal to `a`, and `b` is less than or equal to `d`.

After removing the covered intervals, you need to return the number of remaining intervals.

### Example 1
```text
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
```

### Example 2
```text
Input: intervals = [[1,4],[2,3]]
Output: 1
``` 

### Constraints

* `1 <= intervals.length <= 1000`.
* `intervals[i].length == 2`.
* `0 <= li <= ri <= 10^5`.
* All the given intervals are unique.

## Solution 1: Bruteforce
For each interval `i`, find if any other interval `j` such that `j` covers `i` or `i` covers `j` then remove the smaller one from `intervals`.

### Example 1
For `intervals = [[1,4],[3,6],[2,8]]`.
* With interval `i = [1,4]`, there is no other interval `j` such that covers `i` or `j` covers `i`.
* With interval `i = [3,6]`, there is interval `j = [2,8]` convering `i`. Remove `[3,6]` from `intervals`.

Final `intervals = [[1,4],[2,8]]`.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
inline bool isCovered(vector<int>& i, vector<int>& j) {
    return j[0] <= i[0] && i[1] <= j[1];
}
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    int i = 0;
    while (i < intervals.size() - 1) {
        int j = i + 1;
        bool erase_i = false;
        while (j < intervals.size()) {
            if (isCovered(intervals[i], intervals[j])) {
                intervals.erase(intervals.begin() + i);
                erase_i = true;
                break;
            } else if (isCovered(intervals[j], intervals[i])) {
                intervals.erase(intervals.begin() + j);
            } else {
                j++;
            }
        }
        if (!erase_i) {
            i++;
        }
    }
    return intervals.size();
}
int main() {
    vector<vector<int>> intervals{{1,4},{3,6},{2,8}};
    cout << removeCoveredIntervals(intervals) << endl;
    intervals = {{1,4},{2,3}};
    cout << removeCoveredIntervals(intervals) << endl;
}
```
```text
Output:
2
1
```

This solution effectively removes covered intervals and retains only those that do not have others covering them. The time complexity of this solution is `O(N^3)`, where `N` is the number of intervals, as it involves nested loops and potential removal of intervals from the list.

### Complexity

* Runtime: `O(N^3)`, where `N = intervals.length`.
* Extra space: `O(1)`.

## Solution 2: Using {index}`dictionary order`
You might know how to look up words in a dictionary. 

The word `apple` appears before `candy` in the dictionary because the starting letter `a` of `apple` appears before `c` of `candy` in the English alphabet. 

And `apple` appears after `animal` since the next letter `p` appears after `n`.

The C++ Standard Library uses that dictionary order to compare two `std::vector`s.

### Example 1
Rewriting `intervals = [[1,4],[3,6],[2,8]]` in dictionary order you get `intervals = [[1,4],[2,8],[3,6]]`. In this order, the left bounds of the `intervals` are sorted first.

If `intervals` is sorted like that, you can avoid bruteforce in Solution 1 by a simpler algorithm.

**Check if each interval `i` covers or is covered by some of the previous ones.**

Remember that the left bound of interval `i` is always bigger than or equal to all left bounds of the previous ones. So,

1. `i` is covered by some previous interval if the right bound of `i` is less than some of the right bounds before.
2. Otherwise `i` can only cover its exact previous one that has the same left bound. 

### Code
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    int count = 0;
    int maxRight = -1;
    int preLeft = -1;
    for (auto& i : intervals) {
        if (i[1] <= maxRight) { // i is covered by some previous interval
            count++;
        } else if (i[0] == preLeft) { // i covers its exact previous one
            count++;
        } else {
            preLeft = i[0];
        }
        maxRight = max(maxRight, i[1]);
    }
    return intervals.size() - count;
}
int main() {
    vector<vector<int>> intervals{{1,4},{3,6},{2,8}};
    cout << removeCoveredIntervals(intervals) << endl;
    intervals = {{1,4},{2,3}};
    cout << removeCoveredIntervals(intervals) << endl;
}
```
```text
Output:
2
1
```
This solution first sorts the intervals and then iterates through them while keeping track of whether each interval is covered by others or not. The final result is the count of intervals that are not covered, and it is returned as the output. 

### Complexity

* Runtime: `O(N*logN)`, where `N = intervals.length`.
* Extra space: `O(1)`.

## Key takeaway
* Two `std::vector`s can be compared using dictionary order.
