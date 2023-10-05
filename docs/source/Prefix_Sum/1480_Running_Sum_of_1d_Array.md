# Running Sum of 1d Array

## [Problem statement](https://leetcode.com/problems/running-sum-of-1d-array/)

Given an array called `nums`, calculate the running sum of its elements and return the resulting array. The running sum at index `i` is the sum of elements from index `0` to `i` in the `nums` array.

### Example 1
```text
Input: nums = [1,2,3,4]
Output: [1,3,6,10]
Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
```

### Example 2
```text
Input: nums = [1,1,1,1,1]
Output: [1,2,3,4,5]
Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
```

### Example 3
```text
Input: nums = [3,1,2,10,1]
Output: [3,4,6,16,17]
``` 

### Constraints

* `1 <= nums.length <= 1000`.
* `-10^6 <= nums[i] <= 10^6`.

## Solution 1: Unchange `nums`

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> runningSum(vector<int>& nums) {
    vector<int> rs;
    int s = 0;
    for (int n : nums) {
        s += n;
        rs.push_back(s);
    }
    return rs;
}
void printResult(vector<int>& sums) {
    cout << "[";
    for (int s: sums) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,2,3,4};
    auto rs = runningSum(nums);
    printResult(rs);
    nums = {1,1,1,1,1};
    rs = runningSum(nums);
    printResult(rs);
    nums = {3,1,2,10,1};
    rs = runningSum(nums);
    printResult(rs);
}
```
```text
Output:
[1,3,6,10,]
[1,2,3,4,5,]
[3,4,6,16,17,]
```

### Code explanation

1. A vector `rs` is initialized to store the running sums.

2. An integer variable `s` is initialized to store the running sum.

3. A loop iterates through each element `n` in the `nums` array.

4. Inside the loop, the current element `n` is added to the running sum `s`.

5. The updated running sum `s` is then appended to the result vector `rs` using the `push_back` function. This effectively builds the vector of running sums.

6. The loop continues until all elements in the `nums` array are processed.

7. Finally, the function returns the vector `rs` containing the computed running sums.

In summary, this solution iterates through the input array `nums`, calculates the running sum at each step, and appends the running sums to a result vector. This approach efficiently computes the running sums in a single pass through the array.

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.

## Solution 2: Change `nums`

If `nums` is allowed to be changed, you could use it to store the result directly.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> runningSum(vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        nums[i] += nums[i - 1];
    }
    return nums;
}
void printResult(vector<int>& sums) {
    cout << "[";
    for (int s: sums) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,2,3,4};
    auto rs = runningSum(nums);
    printResult(rs);
    nums = {1,1,1,1,1};
    rs = runningSum(nums);
    printResult(rs);
    nums = {3,1,2,10,1};
    rs = runningSum(nums);
    printResult(rs);
}
```
```text
Output:
[1,3,6,10,]
[1,2,3,4,5,]
[3,4,6,16,17,]
```

### Code explanation

1. The function takes a reference to the vector `nums` as input, allowing modifications to be made directly to the input array.

2. A loop iterates through the array `nums`, starting from index 1 (since the running sum at index 0 is the same as the element at index 0).

3. Inside the loop, the current element `nums[i]` is updated by adding the value of the previous element `nums[i - 1]`. This operation effectively calculates the running sum up to the current index.

4. The loop continues until all elements in the array are processed.

5. After the loop completes, the function returns the modified `nums` array, which now contains the running sums.

In summary, this solution directly modifies the input array `nums` to store the running sums by iteratively updating each element with the cumulative sum of the previous elements. This approach efficiently calculates the running sums in a single pass through the array.

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.


