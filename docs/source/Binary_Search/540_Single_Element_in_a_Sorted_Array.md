# Single Element in a Sorted Array

## Problem statement

[^url]You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

*Return the single element that appears only once.*

Your solution must run in `O(logn)` time and `O(1)` space.

[^url]: https://leetcode.com/problems/single-element-in-a-sorted-array/

### Example 1
```text
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
```

### Example 2
```text
Input: nums = [3,3,7,7,10,11,11]
Output: 10
```
 
### Constraints
* `1 <= nums.length <= 10^5`.
* `0 <= nums[i] <= 10^5`.

## Solution 1: Bruteforce

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int singleNonDuplicate(vector<int>& nums) {
    for (int i = 0; i < nums.size() - 1; i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums[0];
}
int  main() {
    vector<int> nums{1,1,2,3,3,4,4,8,8};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3,3,7,7,10,11,11};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3};
    cout << singleNonDuplicate(nums) << endl;
}
```
```text
Output:
2
10
3
```

### Code explanation

1. The code uses a simple loop to iterate through the array `nums`.

2. Inside the loop, it checks if the current element `nums[i]` is equal to the next element `nums[i + 1]`.

3. If the current element and the next element are not equal, it means that `nums[i]` is the single element because all other elements in the sorted array appear twice. In this case, the code immediately returns `nums[i]` as the result.

4. If the current element and the next element are equal, it means that the single element has not been found yet, and the loop continues to the next pair of elements.

5. The loop continues until `i` reaches the second-to-last element in the array. This is because the code compares elements in pairs, and there's no "next element" to compare with the last element.

6. If the loop completes without finding the single element, it means that the single element is the first element in the array (since it hasn't been found in any pair). Therefore, the code returns `nums[0]` as the result.

In summary, this code takes advantage of the sorted nature of the array to find the single element efficiently. It iterates through the array by comparing elements in pairs, and as soon as it finds a pair of elements that are not equal, it returns the first element of that pair as the result. If no such pair is found, it returns the first element as the single element. 

### Complexity
* Runtime `O(n)`, where `n = nums.length`.
* Memory `O(1)`.

## Solution 2: Binary search
Since `nums` is sorted, you can perform a binary search on it.

Let us divide `nums` into two halves.

If the single element belongs to the right half, all elements of the left half satisfy `nums[2*i] == nums[2*i + 1]`.

Conversely, if the single element belongs to the left half, that condition is violated at the middle element of `nums` (the middle one with an even index).

### Example 1
For `nums = [1,1,2,3,3,4,4,8,8]`:

- The middle element with even index is `nums[4] = 3`. It is not equal to `nums[4 + 1] = 4`. So the single element must be somewhere in the left half `[1,1,2,3,3]`.
- The middle element of `nums = [1,1,2,3,3]` with even index is `nums[2] = 2`, which is not equal to `nums[2 + 1] = 3`. So the single element must be somewhere in the left half `[1,1,2]`.
- The middle element of `nums = [1,1,2]` with even index is `nums[0] = 1 == nums[0 + 1]`. So the single element must be somewhere in the right half `[2]`.
- `nums = [2]` contains only one element. So `2` is the result.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int singleNonDuplicate(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        int mid = (right + left)/4 * 2; // to make sure mid is even
        if (nums[mid] != nums[mid + 1]) {
            right = mid;
        } else {
            left = mid + 2;
        }
    }
    return nums[right];
}
int  main() {
    vector<int> nums{1,1,2,3,3,4,4,8,8};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3,3,7,7,10,11,11};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3};
    cout << singleNonDuplicate(nums) << endl;
}
```
```text
Output:
2
10
3
```

### Code explanation

1. Two integer variables, `left` and `right`, are initialized. `left` is set to `0`, and `right` is set to `nums.size() - 1`, which represents the range of indices to search within the array.

2. The code enters a `while` loop that continues as long as `left` is less than `right`. This loop aims to narrow down the search range to eventually find the single element.

3. Inside the loop, the code calculates the `mid` index using the formula `(right + left) / 4 * 2`. This calculation ensures that `mid` is even because the elements in the array are sorted in pairs, and we need to compare elements in pairs. The division by 4 followed by multiplication by 2 essentially rounds `mid` down to the nearest even number.

4. The code checks if the element at index `mid` is not equal to the element at index `mid + 1`. If this condition is true, it means that the single element is on the left side of the current `mid`. Therefore, the code updates `right` to `mid`, effectively narrowing the search range to the left half of the array.

5. If the elements at index `mid` and `mid + 1` are equal, it means that the single element is on the right side of the current `mid`. Therefore, the code updates `left` to `mid + 2` (skipping the pair of elements). This narrows the search range to the right half of the array.

6. The loop continues to iterate, adjusting the `left` and `right` pointers, until they meet. When they meet, `left` will be pointing to the single element in the array.

7. Finally, the code returns `nums[right]`, which is the single element found after the binary search.

In summary, this solution uses a binary search approach to efficiently find the single element in the sorted array. It takes advantage of the sorted nature of the array and compares elements in pairs, narrowing down the search range until the single element is located. 

### Complexity
* Runtime `O(logn)`, where `n = nums.length`.
* Memory `O(1)`.


