# Last Stone Weight

## [Problem statement](https://leetcode.com/problems/last-stone-weight/)

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

### Code explanation

1. We start by initializing a `priority_queue` called `q` with the given `stones` vector. A `priority_queue` is a max-heap by default, which means it always pops the largest element, making it a suitable choice for finding the heaviest stones efficiently.

2. We enter a loop that continues as long as there are at least two stones in the `priority_queue`. The loop's purpose is to repeatedly smash the heaviest stones together.

3. Inside the loop, we perform the following steps:
   - We retrieve the heaviest stone `y` from the top of the priority queue and remove it using `q.pop()`.
   - We then retrieve the second heaviest stone `x` from the top of the priority queue and remove it as well.
   - We check if `y` and `x` have different weights (i.e., `y != x`). If they are different, it means they can be smashed together, resulting in a new stone with weight `y - x`.
   - If `y` and `x` have the same weight, they completely destroy each other, so we don't add any new stone to the queue.

4. After the loop ends, we check if the priority queue is empty. If it is, it means all stones have been smashed and no stones are left, so we return 0. Otherwise, we return the weight of the last stone remaining, which is at the top of the priority queue.


### Complexity
This solution efficiently simulates the process of smashing stones and finding the last remaining stone by using a max-heap (priority queue) to always select the heaviest stones to smash together.

* Runtime: `O(n*logn)`, where `n = stones.length`.   
* Extra space: `O(n)`.
    
    
    