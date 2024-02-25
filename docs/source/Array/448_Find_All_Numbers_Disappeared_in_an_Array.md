# Find All Numbers Disappeared in an Array
% Easy 

## Problem statement

[^url]You are given an array `nums` of `n` integers, where each integer `nums[i]` falls within the range `[1, n]`. Your task is to find and return an array containing all the integers in the range `[1, n]` that are not present in the given array `nums`.

[^url]: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/ 
### Example 1
```text
Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
```

### Example 2
```text
Input: nums = [1,1]
Output: [2]
```

### Constraints
* `n == nums.length`.
* `1 <= n <= 10^5`.
* `1 <= nums[i] <= n`.
 

### Follow up

Can you solve the problem without using additional memory and achieve a linear runtime complexity? You can assume that the list you return does not count as extra space.

## Solution 1: Marking the appearances by `bool`

You can use a vector of `bool` to mark which value appeared in the array.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> findDisappearedNumbers(const vector<int>& nums) {        

    const int n = nums.size();
    vector<bool> exist(n + 1, false);        
    for (auto& a : nums) {
        exist[a] = true;
    }
    vector<int> result;
    for (int i = 1; i <= n; i++) {
        if (!exist.at(i)) {
            result.push_back(i);
        }
    }
    return result;
}
void print(const vector<int>& nums) {
    cout << "[";
    for (auto& a : nums) {
        cout << a << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    auto result = findDisappearedNumbers(nums);
    print(result);
    nums = {1,1};
    result = findDisappearedNumbers(nums);
    print(result);
}
```
```text
Output:
[5,6,]
[2,]
```

This code declares a vector named `exist` of type `bool` and initializes all of its values to `false`. Its size is declared as `n + 1` where `n = nums.size()` so it can mark the values ranged from `1` to `n`.

Then it performs the marking of all `nums`'s elements to `true`. The ones that are `false` will belong to the result.

### Complexity

* Runtime: `O(n)`, where `n = nums.length`.
    
* Extra space: much less than `O(n)`. [`vector<bool>`](https://en.cppreference.com/w/cpp/container/vector_bool) is optimized for space efficiency; it stores single bits.
    

## Solution 2: Marking the appearances by sign

You could use the indices of the array `nums` to mark the appearances of its elements because they are just a shift (`[1, n]` vs. `[0, n-1]`).

One way of marking the appearance of a value `j` (`1 <= j <= n`) is making the element `nums[j-1]` to be negative. Then the indices `j`'s whose `nums[j-1]` are still positive are the ones that do not appear in `nums`.

### Example 1
With `nums = [4,3,2,7,8,2,3,1]`:

- To indicate `4` is present, make `nums[4-1]` is negative, i.e. changing `nums[4-1] = nums[3]` to `-7`.
- To indicate `3` is present, make `nums[3-1]` is negative, i.e. changing `nums[3-1] = nums[2]` to `-2`.
- And so on.
- `nums` becomes `[-4,-3,-2,-7,8,2,-3,-1]`.
- The positive values `8` corresponds to `nums[4] = nums[5-1]`, indicates `5` was not present in `nums`.
- Similarly, the positive values `2` corresponds to `nums[5] = nums[6-1]`, indicates `6` was not present in `nums`.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> findDisappearedNumbers(vector<int>& nums) {
    const int n = nums.size();
    int j;
    for (int i{0}; i < n; i++) {
        // make sure j is positive since nums[i] might be 
        // changed to be negative in previous steps
        j = abs(nums.at(i));

        // Mark nums[j - 1] as negative to indicate its presence       
        nums[j - 1] = -abs(nums.at(j - 1));
    }
    vector<int> result;
    for (int j{1}; j <= n; j++) {
        // If nums[j - 1] is positive, it means j is missing        
        if (nums.at(j - 1) > 0) {
            result.push_back(j);
        }
    }
    return result;
}
void print(const vector<int>& nums) {
    cout << "[";
    for (auto& a : nums) {
        cout << a << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    auto result = findDisappearedNumbers(nums);
    print(result);
    nums = {1,1};
    result = findDisappearedNumbers(nums);
    print(result);
}
```
```text
Output:
[5,6,]
[2,]
```

The key to this solution is that it utilizes the array to mark the presence of numbers. Negating the value at the index corresponding to each number found in the input array effectively marks that number as present. Then, by iterating through the modified array, it identifies the missing numbers by checking which indices still hold positive values.

### Complexity

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)` (the returned list does not count as extra space).

## Readable code

* Solution 2 helps to avoid allocating extra memory but it is not straightforward to understand.
    
* Though Solution 1 requires some extra space, that memory is not much since `std::vector<bool>` is optimized for space efficiency. Moreover, it is easier to understand than Solution 2.

## Exercise
- [Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array)