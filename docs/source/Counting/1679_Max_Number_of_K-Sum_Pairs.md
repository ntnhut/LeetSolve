# Max Number of K-Sum Pairs

## [Problem statement](https://leetcode.com/problems/max-number-of-k-sum-pairs/)

You're provided with an array of integers called `nums` and an integer `k`. Each operation involves selecting two numbers from the array whose sum is equal to `k`, and then removing them from the array. Your goal is to determine the maximum count of such operations you can perform on the array. 

### Example 1
```text
Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
```

### Example 2
```text
Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
``` 

### Constraints

* `1 <= nums.length <= 10^5`.
* `1 <= nums[i] <= 10^9`.
* `1 <= k <= 10^9`.

## Solution: Count the appearances

You can use a map to count the appearances of the elements of `nums`.

### Example 2
For `nums = [3,1,3,4,3]` and `k = 6`:

* Initialize `count = 0`.
* For `i = 0`: `m[3] = 1`; `k - 3 = 3` but `m[3]` is only `1`, not enough to have two numbers.
* For `i = 1`: `m[1] = 1`; `k - 1 = 5` and `m[5] = 0`.
* For `i = 2`: `m[3] = 2`; `k - 3 = 3` and `m[3] = 2` just enough to have two numbers to perform the sum. `count = 1`. Erase those two values `3`'s from the map: `m[3] = 0`.
* For `i = 3`: `m[4] = 1`; `k - 4 = 2` and `m[2] = 0`.
* For `i = 4`: `m[3] = 1`; `k - 3 = 3` but `m[3]` is only `1`, not enough to have two numbers.
* Final `count = 1`.

### Code
```cpp
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
int maxOperations(vector<int>& nums, int k) {
    unordered_map<int,int> m;
    int count = 0;
    for (int a : nums) {
        m[a]++;
        if (m[k - a] > 0) {
            if (a != k - a || m[a] >= 2) {
                count++;
                m[a]--;
                m[k - a]--;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,2,3,4};
    cout << maxOperations(nums, 5) << endl;
    nums = {3,1,3,4,3};
    cout << maxOperations(nums, 6) << endl;
}
```
```text
Output:
2
1
```

### Code explanation

1. The code initializes an unordered map `m` where keys represent the values in the array `nums`, and values represent the frequency (count) of each value.

2. It also initializes a variable `count` to keep track of the count of valid pairs of elements.

3. The loop then iterates through the elements of the `nums` array. For each element `a` encountered:

   - It increments the count of `a` in the `m` map to keep track of its frequency.
   
   - It checks if there exists a complementary element (`k - a`) in the map `m` with a count greater than 0. If such an element exists:
   
     - It verifies if `a` is not equal to `k - a` (to ensure distinct elements) or if there are at least two occurrences of `a` in the array.
     
     - If either of the above conditions is met, it means a valid pair `(a, k - a)` can be formed. In this case, it increments the `count` and decrements the counts of both `a` and `k - a` in the map `m`. This indicates that these elements have been used in a pair.
     
4. After iterating through the entire array, the function returns the final count, which represents the maximum number of valid pairs of elements that sum up to `k`.


### Complexity
This solution has a time complexity of `O(n)`, where `n` is the number of elements in the `nums` array, as it iterates through the array once. The use of the unordered map allows efficient lookup of complementary elements. The space complexity is also `O(n)` because, in the worst case, all unique elements in `nums` are stored in the `m` map.


* Runtime: `O(n)`.
* Extra space: `O(n)`.
