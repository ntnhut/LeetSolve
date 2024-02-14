# Can Place Flowers
% Easy https://leetcode.com/problems/can-place-flowers/
## Problem statement

You are presented with a long flowerbed containing plots, some of which are planted with flowers (denoted by `1`) and some are empty (denoted by `0`). Flowers cannot be planted in **adjacent** plots. You are given an integer array `flowerbed` representing the layout of the flowerbed, and an integer `n` representing the number of new flowers you want to plant.

Your task is to determine if it is possible to plant `n` new flowers in the `flowerbed` without violating the rule of no-adjacent-flowers. If it is possible, return `true`; otherwise, return `false`.

### Example 1
```text
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
```

### Example 2
```text
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
```

### Constraints

* `1 <= flowerbed.length <= 2 * 10^4`.
* `flowerbed[i]` is `0` or `1`.
* There are no two adjacent flowers in `flowerbed`.
* `0 <= n <= flowerbed.length`.

## Solution: Check the no-adjacent-flowers rule

A new flower can be planted at position `i` only if 
```text
flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0.
```
If the condition is satisfied, the flower can be planted at position `i`. `flowerbed[i]` is now assigned to `1`. Then you can skip checking the rule for the position `i + 1` and go directly to position `i + 2`. 

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n == 0) {
        return true;
    }
    flowerbed.insert(flowerbed.begin(), 0);
    flowerbed.push_back(0);
    int i = 1;
    while (i < flowerbed.size() - 1) {
        if (flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0) {
            flowerbed[i] = 1;
            n--;
            i+=2;
        } else {
            i++;
        }
    }
    return n <= 0;
}
int main() {
    vector<int> flowerbed{1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 1) << endl;
    flowerbed = {1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 2) << endl;
}
```
```text
Output:
1
0
```

This solution efficiently iterates through the flowerbed, planting flowers wherever possible while adhering to the constraints. It returns `true` if it's possible to plant all the required flowers and `false` otherwise.

### Complexity

* Runtime: `O(N)`, where `N = flowerbed.length`.
* Extra space: `O(1)`.

## Implementation tips

* In this implementation, you could insert element `0` to the front and the back of vector `flowerbed` to avoid writing extra code for checking the no-adjacent-flowers rule at `i = 0` and `i = flowerbed.size() - 1`.

* There are a few ways to insert an element to a vector. Here you can see an example of using the methods [`insert`](https://en.cppreference.com/w/cpp/container/vector/insert) and [`push_back`](https://en.cppreference.com/w/cpp/container/vector/push_back) of a [`std::vector`](https://en.cppreference.com/w/cpp/container/vector).

## Ecercise
- [Teemo Attacking](https://leetcode.com/problems/teemo-attacking/)