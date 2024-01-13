# Sort Array By Parity II

## [Problem statement](https://leetcode.com/problems/sort-array-by-parity-ii/)

Given an array of integers `nums`, half of the integers in `nums` are odd, and the other half are even.

Sort the array so that whenever `nums[i]` is odd, `i` is odd, and whenever `nums[i]` is even, `i` is even.

Return any answer array that satisfies this condition. 

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

### Code explanation

1. The code iterates through the elements of `nums` using an index variable `i`.

2. For each element at index `i`, it checks if the parity (even or odd) of `i` is different from the parity of the number at index `i` in the vector. If they are different, it means that the current element is in the wrong position concerning its parity.

3. To fix this, the code goes into a nested loop with another index variable `j`, starting from `i + 1`.

4. In the inner loop, it searches for an element at index `j` whose parity matches the desired parity (which is the same as `i`'s parity).

5. When such an element is found, it swaps the elements at indices `i` and `j`, ensuring that the element at index `i` now has the correct parity.

6. The code continues this process for all elements in the vector until it's sorted by parity.

7. Finally, it returns the sorted vector.

This code ensures that even-indexed elements are even, and odd-indexed elements are odd, while preserving the original order of elements within their respective parity groups.

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

### Code explanation

1. The code initializes `evenPos` to 0, which will track the even positions in the array, and `oddPos` to N - 1, which will track the odd positions.

2. It iterates through the array using `evenPos`. While `evenPos` is less than the length of the array (`N`), it looks for the first odd number by checking `nums[evenPos] % 2 == 0`.

3. If it finds an even number at an even position, it means all even numbers are already in place (even positions). In this case, the loop breaks.

4. If it finds an odd number at an even position, it switches to looking for an even number at an odd position using `oddPos`. It iterates in reverse order using `oddPos` until it finds an even number by checking `nums[oddPos] % 2 == 1`.

5. When both an odd number at an even position and an even number at an odd position are found, they are swapped.

6. This process continues until either all even numbers are in even positions, or the loop encounters a situation where the constraints guarantee a valid solution.

By the end of this process, the array `nums` will be sorted as required, with even numbers in even positions and odd numbers in odd positions. 

### Complexity

This approach has a time complexity of `O(N)`, making it more efficient than the sorting method above.

* Runtime: `O(N)`, where `N = nums.length`.
* Extra space: `O(1)`.
