# Last Stone Weight
% Easy https://leetcode.com/problems/last-stone-weight/
## Problem statement

You are given an array of integers called `stones`, where each `stones[i]` represents the weight of the `i-th` stone.

A game is played with these stones as follows: In each turn, we choose the two heaviest stones and smash them together. Let us say the weights of the two heaviest stones are `x` and `y`, where `x <= y`. The outcome of this smash operation is:

1. If `x` is equal to `y`, both stones are destroyed.
2. If `x` is not equal to `y`, the stone with weight `x` is destroyed, and the stone with weight `y` now has a new weight of `y - x`.

The game continues until there is at most one stone left. Your task is to determine the smallest possible weight of the remaining stone after the game ends. If there are no stones left, return `0`.

### Example 1

```text
Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1, so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2, so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0, so the array converts to [1] then that's the value of the last stone.
```

### Example 2

```text
Input: stones = [1]
Output: 1
```

### Constraints

* `1 <= stones.length <= 30`.
* `1 <= stones[i] <= 1000`.
    

## Solution: Keeping the heaviest stones on top

The only things you want at any time are the two heaviest stones. One way of keeping this condition is by using {index}`std::priority_queue`.

### Code

```cpp
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> q(stones.begin(), stones.end());
    while (q.size() >= 2) {
        int y = q.top();
        q.pop();
        int x = q.top();
        q.pop();
        if (y != x) {
            q.push(y - x);
        }
    }
    return q.empty() ? 0 : q.top();    
}
int main() {
    vector<int> stones{2,7,4,1,8,1};
    cout << lastStoneWeight(stones) << endl;
    stones = {1};
    cout << lastStoneWeight(stones) << endl;
}
```

```text
Output:
1
1
```

This solution efficiently simulates the process of smashing stones and finding the last remaining stone by using a max-heap (priority queue) to always select the heaviest stones to smash together.

### Complexity

* Runtime: `O(n*logn)`, where `n = stones.length`.   
* Extra space: `O(n)`.
    
    
    