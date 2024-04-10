# Product of Array Except Self
% Medium 
## Problem statement

[^url]Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of nums except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in `O(n)` time and without using the division operation.
 
[^url]: https://leetcode.com/problems/product-of-array-except-self/

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
 

### Follow up
* Can you solve the problem in `O(1)` extra space complexity? (The output array does not count as extra space for space complexity analysis.)

## Solution 1: Compute the prefix and suffix products

To avoid division operation, you can compute the prefix product and the suffix one of `nums[i]`.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> productExceptSelf(const vector<int>& nums) {
    const int n = nums.size();
    vector<int> prefix(n);
    prefix[0] = 1;
    // compute all prefix products nums[0]*nums[1]*..*nums[i-1]
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] * nums[i - 1];
    }
    vector<int> suffix(n);        
    suffix[n - 1] = 1;
    // compute all suffix products nums[i+1]*nums[i+2]*..*nums[n-1]
    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = suffix[i + 1] * nums[i + 1];
    }
    vector<int> answer(n);
    for (int i = 0; i < n; i++) {
        answer[i] = prefix[i] * suffix[i];
    }
    return answer;
}
void print(const vector<int>& nums) {
    for (auto& v : nums) {
        cout << v << " ";
    }
    cout << endl;
}
int main() {
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

This solution computes the product of all elements in an array except for the current element. 

It accomplishes this by first computing two arrays: `prefix` and `suffix`. The `prefix` array stores the product of all elements to the left of the current element, while the `suffix` array stores the product of all elements to the right of the current element. By multiplying the corresponding elements from `prefix` and `suffix` arrays, it effectively computes the product of all elements except for the current element at each index. 

This approach optimizes the computation by breaking down the problem into smaller subproblems and leveraging the precomputed prefix and suffix arrays to efficiently compute the final result.

### Complexity

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(n)`.

## Solution 2: Use directly vector `answer` to store the prefix product
In the solution above you can use directly vector `answer` for `prefix` and merge the last two loops into one.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> productExceptSelf(const vector<int>& nums) {
    const int n = nums.size();
    vector<int> answer(n);
    answer[0] = 1;
    // compute all prefix products nums[0]*nums[1]*..*nums[i-1]
    for (int i = 1; i < n; i++) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }
    int suffix = 1;
    for (int i = n - 2; i >= 0; i--) {
        // compute suffix product and the final product the same time
        suffix *= nums[i + 1];
        answer[i] *= suffix;
    }
    return answer;
}
void print(const vector<int>& nums) {
    for (auto& v : nums) {
        cout << v << " ";
    }
    cout << endl;
}
int main() {
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

This code efficiently calculates the products of all elements in the `nums` vector except for the element at each index using two passes through the array. The first pass calculates products to the left of each element, and the second pass calculates products to the right of each element.

### Complexity

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.

## Conclusion

The problem of computing the product of all elements in an array except the element at the current index can be efficiently solved using different approaches. Solution 1 utilizes two separate passes through the array to compute prefix and suffix products independently. By first computing prefix products from left to right and then suffix products from right to left, this solution efficiently calculates the product of all elements except the one at the current index.

Solution 2 offers a more concise approach by combining the computation of prefix and suffix products into a single pass through the array. By iteratively updating a variable to compute suffix products while simultaneously updating the elements of the answer array, this solution achieves the desired result more efficiently with only one pass through the array.

## Exercise
- Construct Product Matrix[^ex].

[^ex]: https://leetcode.com/problems/construct-product-matrix/