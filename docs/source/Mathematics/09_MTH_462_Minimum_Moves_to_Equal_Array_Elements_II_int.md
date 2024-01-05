# Minimum Moves to Equal Array Elements II


## [Problem statement](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

Given an integer array `nums` of size `n`, return the minimum number of moves required to make all array elements equal.

In one move, you can increment or decrement an element of the array by `1`.

### Example 1
```text
Input: nums = [1,2,3]
Output: 2
Explanation:
Only two moves are needed (remember each move increments or decrements one element):
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
```

### Example 2
```text
Input: nums = [1,10,2,9]
Output: 16
``` 

### Constraints

* `n == nums.length`.
* `1 <= nums.length <= 10^5`.
* `-10^9 <= nums[i] <= 10^9`.

## Solution 1: Median - The math behind the problem

You are asked to move all elements of an array to the same value `M`. The problem can be reduced to identifying what `M` is.

First, moving elements of an unsorted array and moving a sorted one are the same. So you can assume `nums` is sorted in some order. Let us say it is sorted in ascending order.

Second, `M` must be in between the minimum element and the maximum one. Apparently!

We will prove that `M` will be the [median](https://en.wikipedia.org/wiki/Median) of `nums`, which is `nums[n/2]` of the sorted `nums`. 

In other words, we will prove that if you choose `M` a value different from `nums[n/2]`, then the number of moves will be increased.

In fact, if you choose `M = nums[n/2] + x`, where `x > 0`, then:

* Each element `nums[i]` that is less than `M` needs more `x` moves, while each `nums[j]` that is greater than `M` can reduce `x` moves. 
* But the number of `nums[i]` is bigger than the number of `nums[j]`.
* So the total number of moves is bigger.

The same arguments apply for `x < 0`.

### Example 3
For `nums = [0,1,2,2,10]`. Its median is `2`. The minimum number of moves is `2 + 1 + 0 + 0 + 8 = 11`.

If you choose `M = 3` (the average value, the mean), the total number of moves is `3 + 2 + 1 + 1 + 7 = 14`. 

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    const int median = nums[nums.size() / 2];
    int moves = 0;
    for (int& a: nums) {
        moves += abs(a - median);
    }
    return moves;
}
int main() {
    vector<int> nums{1,2,3};
    cout << minMoves2(nums) << endl;
    nums = {1,10,2,9};
    cout << minMoves2(nums) << endl;
}
```
```text
Output:
2
16
```

### Code explanation

1. The code starts by sorting the `nums` array in ascending order using `sort(nums.begin(), nums.end())`. Sorting the array allows us to find the median, which is an element that divides the sorted array into two equal halves.

2. After sorting, the code calculates the median as `const int median = nums[nums.size() / 2];`. If the number of elements in `nums` is odd, the median will be the middle element of the sorted array. If it's even, it will be the average of the two middle elements.

3. It initializes a variable `moves` to keep track of the total number of moves needed to make all elements equal.

4. The code then iterates through each element `a` in the sorted `nums` array.

5. For each element `a`, it calculates the absolute difference between `a` and the median (`abs(a - median)`) and adds this difference to the `moves` variable. This represents the number of moves required to make `a` equal to the median.

6. Finally, the code returns the `moves` variable, which contains the minimum number of moves needed to equalize all elements.

### Complexity
The code leverages the concept of the median to minimize the total absolute differences between each element and the median, resulting in the minimum number of moves to equalize the array. The time complexity of this code is `O(n*logn)` due to the sorting step, where `n` is the number of elements in the `nums` array.

* Runtime: `O(n*logn)`.
* Extra space: `O(1)`.


## Solution 2: Using `std::nth_element` to compute the median

What you only need in Solution 1 is the median value. Computing the total number of moves in the `for` loop does not require the array `nums` to be fully sorted. 

In this case, you can use [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element) to reduce the runtime complexity.

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int minMoves2(vector<int>& nums) {
    const int mid = nums.size() / 2;    
    std::nth_element(nums.begin(), nums.begin() + mid, nums.end());
    const int median = nums[mid];
    int moves = 0;
    for (int& a: nums) {
        moves += abs(a - median);
    }
    return moves;
}
int main() {
    vector<int> nums{1,2,3};
    cout << minMoves2(nums) << endl;
    nums = {1,10,2,9};
    cout << minMoves2(nums) << endl;
}
```
```text
Output:
2
16
```

### Code explanation

1. The code starts by calculating the median of the `nums` array without fully sorting it. The median is found by using the {index}`std::nth_element` function, which rearranges elements such that the element at the `mid` position (where `mid` is the index of the middle element after sorting) is the median. This step has a time complexity of `O(n)`.

2. After finding the median, it initializes a variable `moves` to keep track of the total number of moves needed to make all elements equal.

3. The code then iterates through each element `a` in the `nums` array.

4. For each element `a`, it calculates the absolute difference between `a` and the median (`abs(a - median)`) and adds this difference to the `moves` variable. This represents the number of moves required to make `a` equal to the median.

5. Finally, the code returns the `moves` variable, which contains the minimum number of moves needed to equalize all elements.


### Complexity
This code efficiently finds the median of the `nums` array in linear time using `std::nth_element` and then calculates the minimum number of moves to make all elements equal to this median. The overall time complexity of this code is `O(n)`.

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.

```{admonition} Modern C++ tips
:class: tip

In the code of Solution 2, the partial sorting algorithm [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element) will make sure for all indices `i` and `j` that satisfy `0 <= i <= mid <= j < nums.length`, then

    nums[i] <= nums[mid] <= nums[j].

With this property, if `mid = nums.length / 2`, then the value of `nums[mid]` is unchanged no matter how `nums` is sorted or not.
```


