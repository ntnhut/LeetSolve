# Majority Element

## [Problem statement](https://leetcode.com/problems/majority-element/)

Given an array `nums` of size `n`, return the majority element.

The majority element is the element that appears more than `n / 2` times. You may assume that the majority element always exists in the array.

### Example 1
```text
Input: nums = [3,2,3]
Output: 3
```

### Example 2
```text
Input: nums = [2,2,1,1,1,2,2]
Output: 2
``` 

### Constraints

* `n == nums.length`.
* `1 <= n <= 5 * 10^4`.
* `-2^31 <= nums[i] <= 2^31 - 1`.
 

### Follow-up: 
Could you solve the problem in linear time and in `O(1)` space?

## Solution 1: Counting the frequency

### Code
```cpp
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
int majorityElement(vector<int>& nums) {
    unordered_map<int,int> freq;
    const int HALF = nums.size() / 2;
    for (int a : nums) {
        freq[a]++;
        if (freq[a] > HALF) {
            return a;
        }
    }
    return nums[0];
}
int main() {
    vector<int> nums{3,2,3};
    cout << majorityElement(nums) << endl;
    nums = {2,2,1,1,1,2,2};
    cout << majorityElement(nums) << endl;
}
```
```text
Output:
3
2
```

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(n)`.

## Solution 2: Sorting and picking the middle element

### Code
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size()/2];
}
int main() {
    vector<int> nums{3,2,3};
    cout << majorityElement(nums) << endl;
    nums = {2,2,1,1,1,2,2};
    cout << majorityElement(nums) << endl;
}
```
```text
Output:
3
2
```

## Solution 3: Partial sort

Since you are interested in only the middle element after sorting, the partial sorting algorithm [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element) can be used in this case to reduce the cost of the full sorting.

### Code
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int majorityElement(vector<int>& nums) {
    const int mid = nums.size() / 2;    
    std::nth_element(nums.begin(), nums.begin() + mid, nums.end());
    return nums[mid];
}
int main() {
    vector<int> nums{3,2,3};
    cout << majorityElement(nums) << endl; // 3
    nums = {2,2,1,1,1,2,2};
    cout << majorityElement(nums) << endl; // 2
}
```
```text
Output:
3
2
```

### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.


## Modern C++ notes

In the code of Solution 3, the partial sorting algorithm [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element) will make sure for all indices `i` and `j` that satisfy `0 <= i <= mid <= j < nums.length`,

```text
nums[i] <= nums[mid] <= nums[j].
```

In other words, `nums[mid]` divides the array `nums` into two groups: all elements that are less than or equal to `nums[mid]` and the ones that are greater than or equal to `nums[mid]`. 

Those two groups are unsorted. That is why the algorithm is called *partial* sorting. 


