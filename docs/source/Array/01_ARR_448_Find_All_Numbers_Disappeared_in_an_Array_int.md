# Find All Numbers Disappeared in an Array

## [Problem statement](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

You are given an array `nums` of `n` integers, where each integer `nums[i]` falls within the range `[1, n]`. Your task is to find and return an array containing all the integers in the range `[1, n]` that are not present in the given array `nums`.

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
vector<int> findDisappearedNumbers(vector<int>& nums) {        
    vector<bool> exist(nums.size() + 1, false);        
    for (auto& i : nums) {
        exist[i] = true;
    }
    vector<int> result;
    for (int i = 1; i <= nums.size(); i++) {
        if (!exist.at(i)) {
            result.push_back(i);
        }
    }
    return result;
}
void print(vector<int>& nums) {
    cout << "[";
    for (auto& n : nums) {
        cout << n << ",";
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

One way of marking the appearance of an index `j` is making the element `nums[j]` to be negative. Then the indices `j`'s whose `nums[j]` are unchanged (still positive) are the ones that do not appear in `nums`.

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> findDisappearedNumbers(vector<int>& nums) {
    int j;
    for (int i{0}; i < nums.size(); i++) {
        j = abs(nums.at(i));
        nums[j - 1] = -abs(nums.at(j - 1));
    }
    vector<int> result;
    for (int i{1}; i <= nums.size(); i++) {
        if (nums.at(i - 1) > 0) {
            result.push_back(i);
        }
    }
    return result;
}
void print(vector<int>& nums) {
    cout << "[";
    for (auto& n : nums) {
        cout << n << ",";
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
