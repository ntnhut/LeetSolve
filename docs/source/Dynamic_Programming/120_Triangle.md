# Triangle
% Medium
## Problem statement

[^url]You're provided with a `triangle` array. Your goal is to find the smallest possible sum of a path from the top of the triangle to the bottom.

At each step, you have the option to move to an adjacent number in the row below. Specifically, if you're at index `i` in the current row, you can move to either index `i` or index `i + 1` in the next row. 

[^url]: https://leetcode.com/problems/triangle/
### Example 1
```text
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
```

### Example 2
```text
Input: triangle = [[-10]]
Output: -10
``` 

### Constraints

* `1 <= triangle.length <= 200`.
* `triangle[0].length == 1`.
* `triangle[i].length == triangle[i - 1].length + 1`.
* `-10^4 <= triangle[i][j] <= 10^4`.
 

### Follow up
- Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?

## Solution 1: Store all minimum paths

You can store all minimum paths at every positions `(i,j)` so you can compute the next ones with this relationship.

```text
minPath[i][j] = triangle[i][j] + min(minPath[i - 1][j - 1], minPath[i - 1][j]);
```

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    const int n = triangle.size(); // triangle's height
    vector<vector<int>> minPath(n);
    minPath[0] = triangle[0];
    for (int i = 1; i < n; i++) {
        const int N = triangle[i].size();
        minPath[i].resize(N);
        // left most number
        minPath[i][0] = triangle[i][0] + minPath[i-1][0];
        for (int j = 1; j < N - 1; j++) {
            minPath[i][j] = triangle[i][j] + min(minPath[i-1][j-1], minPath[i-1][j]);
        }
        // right most number
        minPath[i][N-1] = triangle[i][N-1] + minPath[i-1][N-2];

    }
    // pick the min path among the ones (begin -> end)
    // go to the bottom (n-1)
    return *min_element(minPath[n-1].begin(), minPath[n-1].end());
}
int main() {
    vector<vector<int>> triangle{{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << minimumTotal(triangle) << endl;
    triangle = {{-10}};
    cout << minimumTotal(triangle) << endl;
}
```
```text
Output:
11
-10
```


This solution finds the minimum path sum from the top to the bottom of a triangle, represented as a vector of vectors. It uses dynamic programming to calculate the minimum path sum.

The algorithm initializes a `minPath` vector of vectors to store the minimum path sum for each element in the `triangle`. It starts by setting the first row of `minPath` to be the same as the first row of the `triangle`.

Then, it iterates through the rows of the `triangle` starting from the second row. For each element in the current row, it calculates the minimum path sum by considering the two possible paths from the previous row that lead to that element. It takes the minimum of the two paths and adds the value of the current element. This way, it accumulates the minimum path sum efficiently.

The algorithm continues this process until it reaches the last row of the `triangle`. Finally, it returns the minimum element from the last row of `minPath`, which represents the minimum path sum from top to bottom.


### Complexity

* Runtime: `O(n^2)`, where `n` is the number of rows in the `triangle`.
* Extra space: `O(n^2)`.

## Solution 2: Store only the minimum paths of each row

You do not need to store all paths for all rows. The computation of the next row only depends on its previous one.

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    const int n = triangle.size();
    // store only min path for each row
    vector<int> minPath(n);
    minPath[0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        // right most number
        minPath[i] = triangle[i][i] + minPath[i - 1];
        for (int j = i - 1; j > 0; j--) {
            minPath[j] = triangle[i][j] + min(minPath[j - 1], minPath[j]);
        }
        // left most number
        minPath[0] = triangle[i][0] + minPath[0];
    }
    return *min_element(minPath.begin(), minPath.end());
}
int main() {
    vector<vector<int>> triangle{{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << minimumTotal(triangle) << endl;
    triangle = {{-10}};
    cout << minimumTotal(triangle) << endl;
}
```
```text
Output:
11
-10
```

### Complexity

* Runtime: `O(n^2)`, where `n` is the number of rows in the triangle.
* Extra space: `O(n)`.


