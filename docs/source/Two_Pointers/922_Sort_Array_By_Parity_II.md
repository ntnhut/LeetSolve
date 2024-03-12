# Sort Array By Parity II
% Easy
## Problem statement

[^url]Given an array of integers `nums`, half of the integers in `nums` are odd, and the other half are even.

Sort the array so that whenever `nums[i]` is odd, `i` is odd, and whenever `nums[i]` is even, `i` is even.

Return any answer array that satisfies this condition. 

[^url]: https://leetcode.com/problems/sort-array-by-parity-ii/
### Example 1
```plain
Input: nums = [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
```

### Example 2
```plain
Input: nums = [2,3]
Output: [2,3]
``` 

### Constraints:

* `2 <= nums.length <= 2 * 10^4`.
* `nums.length` is even.
* Half of the integers in `nums` are even.
* `0 <= nums[i] <= 1000`.

## Solution 1: Bubble Sort
For each `0 <= i < nums.length`, if `nums[i]` has the same parity with `i`, you do nothing. Otherwise you need to find another `nums[j]` that has the same parity with `i` to swap with `nums[i]`.

### Example 1
For `nums = [4,2,5,7]`:
* `nums[0] = 4` is even like `i = 0`.
* `nums[1] = 2` is even, unlike `i = 1` is odd. Found `nums[2] = 5` is odd. Swap `nums[1] <-> nums[2]`. `nums[2]` becomes `2` while `nums[1]` becomes `5` is odd like `i = 1`.
* `nums[2] = 2` is even, like `i = 2`.
* `nums[3] = 7` is odd like `i = 3`.

### Code
```cpp
#include<vector>
#include<iostream>
using namespace std;
vector<int> sortArrayByParityII(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (i % 2 != nums[i] % 2) {
            // find suitable nums[j] to swap
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] % 2 == i % 2) {
                    swap(nums[i], nums[j]);
                    break;
                }
            }
        }
    }
    return nums;
}
void print(vector<int>& nums) {
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;
}
int main() {
    vector<int> nums = {4,2,5,7};
    auto result = sortArrayByParityII(nums);
    print(result);
    nums = {1,0,7,3,8,9,2,5,4,1,2,4};
    result = sortArrayByParityII(nums);
    print(result);
    nums = {3,4};
    result = sortArrayByParityII(nums);
    print(result);
    nums = {648,831,560,986,192,424,997,829,897,843};
    result = sortArrayByParityII(nums);
    print(result);
}
```
```plain
Output:
4 5 2 7 
0 1 8 3 2 9 4 5 2 1 4 7
4 3
648 831 560 997 192 829 986 897 424 843
```

This solution iteratively scans through the array and swap elements to ensure that the parity (even or odd) of each element matches its index modulo 2. 

The algorithm iterates over each index of the array. For each index `i`, if the parity of the element at index `i` does not match `i % 2`, it implies that the element is in the wrong position. In such cases, the algorithm searches for the next element with the correct parity (i.e., even or odd) starting from index `i + 1`. Once found, it swaps the elements at indices `i` and `j`, where `j` is the index of the next element with the correct parity. 

By performing these swaps, the algorithm ensures that each element is at the correct position based on its parity. 

This approach optimizes the sorting process by performing a single pass through the array and minimizing the number of swaps required to achieve the desired parity arrangement.

### Complexity
* Runtime: `O(N^2)`, where `N = nums.length`.
* Extra space: `O(1)`.

## Solution 2: Two pointers - Make use of the problem’s constraints

In the Bubble Sort approach, you do not make use of the ***constraint*** that **half of the integers in `nums` are even**. Because of that, these are unnecessary things:

1. The loops scan through full `nums`.
2. The loops are nested. That increases the complexity.
3. The `swap(nums[i], nums[j])` happens even when `nums[j]` was already in place, i.e. `nums[j]` had the same parity with `j` (Why to move it?).

Here is a two-pointer approach which takes the important ***constraint*** into account.

### Code
```cpp
#include<vector>
#include<iostream>
#include <algorithm>
using namespace std;
vector<int> sortArrayByParityII(vector<int>& nums) {
    int N = nums.size();
    int evenPos = 0;
    int oddPos = N - 1;
    while (evenPos < N) {
        // find the nums[evenPos] that is odd for swapping
        while (evenPos < N && nums[evenPos] % 2 == 0) {
            evenPos += 2;
        }
        // If not found, it means all even nums are in place. Done! 
        if (evenPos >= N) {
            break;
        }
        // Otherwise, the problem's constraint makes sure 
        // there must be some nums[oddPos] that is even for swapping
        while (oddPos >= 0 && nums[oddPos] % 2 == 1) {
            oddPos -= 2;
        } 
        swap(nums[evenPos], nums[oddPos]);
    }
    return nums;
}
void print(vector<int>& nums) {
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;
}
int main() {
    vector<int> nums = {4,2,5,7};
    auto result = sortArrayByParityII(nums);
    print(result);
    nums = {1,0,7,3,8,9,2,5,4,1,2,4};
    result = sortArrayByParityII(nums);
    print(result);
    nums = {3,4};
    result = sortArrayByParityII(nums);
    print(result);
    nums = {648,831,560,986,192,424,997,829,897,843};
    result = sortArrayByParityII(nums);
    print(result);
}
```
```plain
Output:
4 5 2 7 
0 1 8 3 2 9 4 5 2 1 4 7
4 3
648 831 560 997 192 829 986 897 424 843
```

### Complexity

* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(1)`.

## Conclusion

Solution 2 uses two pointers, one starting from the beginning of the array (`evenPos`) and the other starting from the end (`oddPos`), to efficiently identify misplaced elements. 

By incrementing `evenPos` by 2 until an odd element is found and decrementing `oddPos` by 2 until an even element is found, the algorithm can swap these elements to ensure that even-indexed elements contain even values and odd-indexed elements contain odd values. This process iterates until all even and odd elements are correctly positioned.

## Exercise
- Rearrange Array Elements by Sign[^ex].

[^ex]: https://leetcode.com/problems/rearrange-array-elements-by-sign/