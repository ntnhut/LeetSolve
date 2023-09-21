# Remove Duplicates from Sorted Array II

## [Problem statement](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)

Given an integer array `nums` that is already sorted in non-decreasing order, you need to remove duplicates from it such that each unique element appears at most twice. The relative order of the elements should remain unchanged.

Since it's impossible to change the length of the array in some programming languages, you must place the result in the first part of the `nums` array. In other words, if there are `k` elements after removing the duplicates, the first `k` elements of `nums` should contain the final result. Anything beyond the first `k` elements is not important.

You should return the value of `k` after placing the final result in the first `k` slots of the `nums` array.

The key requirement is that you must accomplish this task without using extra space for another array. It must be done by modifying the input array `nums` in-place, using only $O(1)$ extra memory.

### Example 1
```text
Input: nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
```
### Example 2
```text
Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
``` 

### Constraints
* `1 <= nums.length <= 3 * 10^4`.
* `-10^4 <= nums[i] <= 10^4`.
* `nums` is sorted in **non-decreasing** order.

## Solution 1: Erasing the duplicates
In order for each unique element appears **at most twice**, you have to erase the further appearances if they exist. 

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

### Code explanation

1. Inside the loop, it checks if the element at index `i` is equal to the element two positions before it. 

2. If the condition is met, it means there are more than two occurrences of the current element. We need to remove the excess duplicates while preserving two instances. To do this, a second while loop is used until the duplicate elements are no longer found. At this point, `j` will be the index of the first element that is different from the current element.

3. After finding the range of duplicate elements to remove (from index `i` to `j-1`, inclusive), it uses the `vector`'s `erase` function to remove these elements from the `nums` array. This effectively keeps only two instances of the current element.

4. If the condition in step 2 is not met (i.e., there are at most two occurrences of the current element), it moves the index `i` to the next unique element in the array.

5. Repeat steps 2 to 4 until `i` has traversed the entire array. The while loop ensures that all duplicate elements beyond two occurrences are removed while maintaining the order of unique elements.

6. Once the loop finishes, the `nums` array contains only unique elements with at most two occurrences of each. Return the size of the modified array using `nums.size()`.

In summary, this solution efficiently removes duplicates from the sorted array by checking for duplicates and erasing the excess occurrences while preserving two instances of each unique element. It then returns the length of the modified array. 

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
You might need to avoid the `erase()` method in the solution above to reduce the complexity. Moreover, the problem only cares about the first `k` elements of the array `nums` after removing the duplicates.

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

### Code explanation

1. The code checks the size of the input array `nums`. If it has 2 or fewer elements, there's no need to perform any removals, so the function simply returns the size of the original array.

2. It initializes two variables:
   - `k`: This will represent the length of the resulting array after removing duplicates (initially set to 2 since we allow up to two occurrences of each element).
   - `i`: This is an iterator that starts from the third element (index 2) of the array and is used to traverse the array.

3. It starts a loop that iterates from the third element (`i = 2`) to the end of the array.

4. Inside the loop, it compares the current element at index `i` with the element at index `k - 2`. This comparison checks if the current element is greater than the element two positions before it. If it is, this means it's a new element. Otherwise, it is a third occurrence of the same element, which we want to skip.

5. If the current element is greater than the element at index `k - 2`, update the element at index `k` with the current element. Then, increment `k` to indicate that a new unique element has been found.

6. Continue iterating through the array by incrementing `i`.

7. Once the loop finishes, the array up to index `k - 1` contains the unique elements with at most two occurrences each, and the rest of the array can be ignored.

8. Finally, return the value of `k`, which represents the length of the resulting array.


### Complexity
This solution effectively modifies the input array in-place, removing any duplicates that occur more than twice while maintaining the desired order of unique elements. It does so in a single pass through the array, resulting in a time complexity of `O(N)`, where `N` is the number of elements in the array.

* Runtime: `O(N)`, where `N = nums.size()`.
* Extra space: `O(1)`.



