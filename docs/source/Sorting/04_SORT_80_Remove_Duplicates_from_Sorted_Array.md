# Remove Duplicates from Sorted Array II
% Medium https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
## Problem statement

Given an integer array `nums` already sorted in non-decreasing order, you must remove duplicates so that each unique element appears at most twice. The relative order of the elements should remain unchanged.

Since changing the array's length in some programming languages is impossible, you must place the result in the first part of the `nums` array. In other words, if there are `k` elements after removing the duplicates, the first `k` elements of `nums` should contain the final result. Anything beyond the first `k` elements is not important.

You should return the value of `k` after placing the final result in the first `k` slots of the `nums` array.

The key requirement is to accomplish this task without using extra space for another array. It must be done by modifying the input array `nums` in-place, using only `O(1)` extra memory.

### Example 1

```text
Input: nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2, and 3, respectively.
What you leave does not matter beyond the returned k (hence, they are underscores).
```

### Example 2

```text
Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3, and 3, respectively.
What you leave does not matter beyond the returned k (hence, they are underscores).
```

### Constraints

* `1 <= nums.length <= 3 * 10^4`.   
* `-10^4 <= nums[i] <= 10^4`.
* `nums` is sorted in **non-decreasing** order.
    

## Solution 1: Erasing the duplicates

In order for each unique element to appear **at most twice**, you have to erase the further appearances if they exist.

Since the array `nums` is sorted, you can determine that existence by checking if `nums[i] == nums[i-2]` for `2 <= i < nums.length`.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
int removeDuplicates(vector<int>& nums) {
    int i = 2;
    while (i < nums.size()) {
        if (nums[i] == nums[i-2]) {
            int j = i;
            while (j < nums.size() && nums[j] == nums[i]) {
                j++;
            }
            nums.erase(nums.begin() + i, nums.begin() + j);
        } else {
            i++;
        }
    }
    return nums.size();
}
void printResult(const int k, const vector<int>& nums) {
    cout << k << ", [";
    for (int i = 0; i < k ; i++) {
        cout << nums[i] << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,1,1,2,2,3};
    printResult(removeDuplicates(nums), nums);
    nums = {0,0,1,1,1,1,2,3,3};
    printResult(removeDuplicates(nums), nums);
}
```

```text
Output:
5, [1,1,2,2,3,]
7, [0,0,1,1,2,3,3,]
```

This solution efficiently removes duplicates from the sorted array by checking for duplicates and erasing the excess occurrences while preserving two instances of each unique element. It then returns the length of the modified array.

### Complexity

* Runtime:
    
    * Worst case: `O(N^2/3)`, where `N = nums.size()`. The complexity of the [`erase()`](https://en.cppreference.com/w/cpp/container/vector/erase) method is linear in `N`. The worst case is when `erase()` is called maximum `N/3` times.
        
    
    ```text
    Example of the worst case:
    nums = [1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6].
    ```
    
    * On average: `O(N)` since the number of `erase()` calls is `O(1)`.
        
* Extra space: `O(1)`.
    

## Solution 2: Reassigning the satisfying elements

You might need to avoid the `erase()` method in the solution above to reduce the complexity. Moreover, after removing the duplicates, the problem only cares about the first `k` elements of the array `nums`.

If you look at the final result after removing duplication, the **expected** `nums` satisfies

```text
nums[i] > nums[i-2] for 2 <= i < nums.length.
```

You can use this invariant to **reassign** the array `nums` only the satisfied elements.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
int removeDuplicates(vector<int>& nums) {
    if (nums.size() <= 2) {
        return nums.size(); 
    } 
    int k = 2; 
    int i = 2;
    while (i < nums.size()) {
        if (nums[i] > nums[k - 2]) {
            nums[k++] = nums[i];
        }
        i++;
    }
    return k;
}
void printResult(const int k, const vector<int>& nums) {
    cout << k << ", [";
    for (int i = 0; i < k ; i++) {
        cout << nums[i] << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,1,1,2,2,3};
    printResult(removeDuplicates(nums), nums);
    nums = {0,0,1,1,1,1,2,3,3};
    printResult(removeDuplicates(nums), nums);
}
```

```text
Output:
Output:
5, [1,1,2,2,3,]
7, [0,0,1,1,2,3,3,]
```

This solution effectively modifies the input array in-place, removing duplicates that occur more than twice while maintaining the desired order of unique elements. It does so in a single pass through the array, resulting in a time complexity of `O(N)`, where `N` is the number of elements in the array.

### Complexity

* Runtime: `O(N)`, where `N = nums.size()`.
    
* Extra space: `O(1)`.

## Exercise
- [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)