# Product of Array Except Self

## [Problem statement](https://leetcode.com/problems/product-of-array-except-self/)
Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of nums except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in `O(n)` time and without using the division operation.
 

### Example 1
```plain
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

### Example 2
```plain
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```
 

### Constraints

* `2 <= nums.length <= 10^5`.
* `-30 <= nums[i] <= 30`.
* The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.
 

**Follow up**: Can you solve the problem in `O(1)` extra space complexity? (The output array does not count as extra space for space complexity analysis.)

## Solution 1: Compute the prefix and suffix products

To avoid division operation, you can compute the prefix product and the suffix one of `nums[i]`.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> productExceptSelf(vector<int>& nums) 
{
    const int n = nums.size();
    vector<int> prefix(n);
    prefix[0] = 1;
    for (int i = 1; i < n; i++) 
    {
        prefix[i] = prefix[i - 1] * nums[i - 1];
    }
    vector<int> suffix(n);        
    suffix[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) 
    {
        suffix[i] = suffix[i + 1] * nums[i + 1];
    }
    vector<int> answer(n);
    for (int i = 0; i < n; i++) 
    {
        answer[i] = prefix[i] * suffix[i];
    }
    return answer;
}
void print(vector<int>& nums) 
{
    for (auto& v : nums) 
    {
        cout << v << " ";
    }
    cout << endl;
}
int main() 
{
    vector<int> nums = {1, 2, 3, 4};
    auto answer = productExceptSelf(nums);
    print(answer);
    nums = {-1, 1, 0, -3, 3};
    answer = productExceptSelf(nums);
    print(answer);
}
```
```plain
Output:
24 12 8 6 
0 0 9 0 0
```

### Code explanation

1. The code stores the length of the input vector `nums` in the variable `n`.

2. It initializes an empty vector called `prefix` of length `n`. The `prefix` vector will store the product of all elements to the left of the current element in `nums`.

3. It initializes the first element of the `prefix` vector at index 0 to be 1. Since there are no elements to the left of the first element, its product is defined as 1.

4. For each index `i` in the loop, it calculates the product of all elements to the left of `i` in `nums` and stores it in the `prefix` vector at index `i`. This is done by multiplying the previous element in the `prefix` vector with the corresponding element in `nums`.

5. The code initializes another empty vector called `suffix` of the same length `n`. The `suffix` vector will store the product of all elements to the right of the current element in `nums`.

6. It initializes the last element of the `suffix` vector at index `n - 1` to be 1. Since there are no elements to the right of the last element, its product is defined as 1.

7. The code loops through `nums` in reverse order, starting from index `n - 2` and going down to index 0. For each index `i`, it calculates the product of all elements to the right of `i` in `nums` and store it in the `suffix` vector at index `i`.

8. It initializes an empty vector called `answer` of the same length `n`. This vector will store the final result.

9. For each index `i` in the loop, it calculates the final answer at that index by multiplying the corresponding elements from the `prefix` and `suffix` vectors and store it in the `answer` vector.

10. The code returns the `answer` vector, which contains the desired products of all elements in `nums` except for the element at each respective index.

### Complexity
The time complexity of this code is `O(n)` because it iterates through the `nums` vector three times in separate loops, and each loop has a linear time complexity with respect to the length of `nums`. The space complexity is `O(n)` as well because it uses additional vectors (`prefix` and `suffix`) of the same length as `nums`.

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(n)`.

## Solution 2: Use directly vector `answer` to store the prefix product
In the solution above you can use directly vector `answer` for `prefix` and merge the last two loops into one.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> productExceptSelf(vector<int>& nums) 
{
    const int n = nums.size();
    vector<int> answer(n);
    answer[0] = 1;
    for (int i = 1; i < n; i++) 
    {
        answer[i] = answer[i - 1] * nums[i - 1];
    }
    int suffix = 1;
    for (int i = n - 2; i >= 0; i--) 
    {
        suffix *= nums[i + 1];
        answer[i] *= suffix;
    }
    return answer;
}
void print(vector<int>& nums) 
{
    for (auto& v : nums) 
    {
        cout << v << " ";
    }
    cout << endl;
}
int main() 
{
    vector<int> nums = {1, 2, 3, 4};
    auto answer = productExceptSelf(nums);
    print(answer);
    nums = {-1, 1, 0, -3, 3};
    answer = productExceptSelf(nums);
    print(answer);
}
```
```plain
Output:
24 12 8 6 
0 0 9 0 0
```

### Code explanation

1. An integer variable `n` is set to the size (number of elements) of the input vector `nums`.

2. The code creates a new integer vector called `answer` of the same size as `nums`. This vector will store the final results.

3. It initializes the first element of the `answer` vector at index 0 to be 1. This is because the product of all elements to the left of the first element is defined as 1.

4. For each element at index `i` in the loop, it calculates the product of all elements to the left of it and store it in the `answer` vector at index `i`. This is done by multiplying the previous element in the `answer` vector with the corresponding element in `nums`.

5. It initializes an integer variable `suffix` to 1. This variable will be used to keep track of the product of all elements to the right of the current element in `nums`.

6. For each element at index `i` in the reverse-order loop, it calculates the product of all elements to the right of it and multiply it with the corresponding element in the `answer` vector at index `i`. It updates the `suffix` by multiplying it with the next element to the right in `nums`.

7. The code returns the `answer` vector, which now contains the desired products of all elements in `nums` except for the element at each respective index.

### Complexity
This code efficiently calculates the products of all elements in the `nums` vector except for the element at each index using two passes through the array. The first pass calculates products to the left of each element, and the second pass calculates products to the right of each element. The time complexity is `O(n)`, and the space complexity is `O(1)` as it only uses a single additional integer (`suffix`) and reuses the `answer` vector to store the final results.

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.
