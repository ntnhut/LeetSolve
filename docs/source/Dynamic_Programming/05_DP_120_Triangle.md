# Triangle

## [Problem statement](https://leetcode.com/problems/triangle/)

Given a `triangle` array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.

 

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
 

**Follow up**: Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?

## Solution 1: Store all minimum paths

You can store all minimum paths at every positions `(i,j)` so you can compute the next ones with this relationship.

```text
minTotal[i][j] = triangle[i][j] + min(minTotal[i - 1][j - 1], minTotal[i - 1][j]);
```

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> minTotal(triangle.size());
    minTotal[0] = triangle[0];
    for (int i = 1; i < triangle.size(); i++) {
        const int N = triangle[i].size();
        minTotal[i].resize(N);
        for (int j = 0; j < N; j++) {
            if (j == 0) {
                minTotal[i][j] = triangle[i][j] + minTotal[i - 1][j];
            } else if (j == N - 1) {
                minTotal[i][j] = triangle[i][j] + minTotal[i - 1][j - 1];
            } else {
                minTotal[i][j] = triangle[i][j] + min(minTotal[i - 1][j - 1], minTotal[i - 1][j]);
            }
        }
    }
    return *min_element(minTotal[triangle.size() - 1].begin(), minTotal[triangle.size() - 1].end());
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
* Runtime: `O(n*n/2)`, where `n = triangle.length`.
* Extra space: `O(n*n/2)`.

## Solution 2: Store only the minimum paths of each row

You do not need to store all paths for all rows. The computation of the next row only depends on its previous one.

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    vector<int> minTotal(triangle.size());
    minTotal[0] = triangle[0][0];
    for (int i = 1; i < triangle.size(); i++) {
        minTotal[i] = triangle[i][i] + minTotal[i - 1];
        for (int j = i - 1; j > 0; j--) {
            minTotal[j] = triangle[i][j] + min(minTotal[j - 1], minTotal[j]);
        }
        minTotal[0] = triangle[i][0] + minTotal[0];
    }
    return *min_element(minTotal.begin(), minTotal.end());
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
* Runtime: `O(n*n/2)`, where `n = triangle.length`.
* Extra space: `O(n)`.


