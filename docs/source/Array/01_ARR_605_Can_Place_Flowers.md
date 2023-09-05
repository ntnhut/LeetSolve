# Can Place Flowers

## [Problem statement](https://leetcode.com/problems/can-place-flowers/)

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

### Code explanation

1. First, the code checks if the value of `n` is zero. If `n` is zero, it means there are no flowers to plant, and the function immediately returns `true`, indicating that it's possible to place zero flowers anywhere.

2. To simplify the logic when checking adjacent elements, the code adds a leading and trailing zero to the `flowerbed` vector. This ensures that the first and last positions in the flowerbed are treated as empty (zero) when checking adjacent elements.

3. A loop starts from `i = 1`, representing the current position in the flowerbed. It iterates through the flowerbed, excluding the trailing zero added before. The loop continues until `i` reaches the second-to-last position in the flowerbed.

4. A condition checks if the current position and its adjacent positions are all empty (represented by zeros). If this condition is met, it means we can plant a flower at the current position.

5. If the condition satisfies, the code sets the current position to 1, indicating that a flower has been plantedand decrements the number of flowers to plant (`n`) because one flower has been planted at the current position.

6. After planting a flower, the loop skips two positions ahead since we cannot plant another flower in the adjacent position due to the constraint.

7. If the condition is not met, it means we cannot plant a flower at the current position. In this case, we simply move to the next position in the flowerbed.

8. Finally, after the loop has processed all positions in the flowerbed, the code checks whether `n` has become less than or equal to zero. If `n` is less than or equal to zero, it means that all required flowers have been planted successfully, and the function returns `true`. Otherwise, it returns `false`, indicating that it was not possible to plant all the required flowers in the flowerbed while following the given constraints.

In summary, this code efficiently iterates through the flowerbed, planting flowers wherever possible while adhering to the constraints. It returns `true` if it's possible to plant all the required flowers and `false` otherwise.

### Complexity
* Runtime: $O(N)$, where $N$ is `flowerbed.length`.
* Extra space: $O(1)$.

```{admonition} Implementation tips
:class: tip

* In this implementation, you could insert element `0` to the front and the back of vector `flowerbed` to avoid writing extra code for checking the no-adjacent-flowers rule at `i = 0` and `i = flowerbed.size() - 1`.

* There are a few ways to insert an element to a vector. Here you can see an example of using the methods [`insert`](https://en.cppreference.com/w/cpp/container/vector/insert) and [`push_back`](https://en.cppreference.com/w/cpp/container/vector/push_back) of a [`std::vector`](https://en.cppreference.com/w/cpp/container/vector).

```