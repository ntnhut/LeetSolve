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

### Code explanation

The code declares a vector named `exist` of type `bool` and initializes all of its values to `false`. Its size is declared as `n + 1` where `n = nums.size()` so it can mark the values ranged from `1` to `n`.
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

### Code explanation

1. The code declares an integer `j` which will be used to store the absolute value of elements in the `nums` array.

2. Inside the first loop, the code modifies the element at index `j - 1` of the `nums` array by negating its absolute value. This step marks the presence of the number `j`. If the number at index `j - 1` is positive, it means that `j` is present in the array. If it's negative, it means `j` is missing.

3. After the first loop completes, the `nums` array contains negative values in positions where corresponding numbers are present and positive values where numbers are missing.

4. A new vector called `result` is created to store the disappeared numbers: `vector<int> result;`.

5. Inside the second loop, the code checks if the number at index `i - 1` in the `nums` array is positive. If it is, it means that the number `i` is missing because the corresponding position wasn't marked during the first loop. In this case, the code adds `i` to the `result` vector using `result.push_back(i);`.

6. Finally, the function returns the `result` vector, which contains all the disappeared numbers in the `nums` array.

### Complexity

This solution efficiently finds the disappeared numbers in an array by using the sign of elements to mark their presence or absence. It leverages the fact that the array contains numbers in the range of `1` to `n`, and it avoids using additional data structures.

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)` (the returned list does not count as extra space).

```{admonition} Readable code
:class: tip
* Solution 2 helps to avoid allocating extra memory but it is not straightforward to understand.
    
* Though Solution 1 requires some extra space, that memory is not much since `vector<bool>` is optimized for space efficiency. Moreover, it is easier to understand than Solution 2.

```