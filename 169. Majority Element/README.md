## 169. Majority Element
Tag: easy

### Problem statement

Given an array `nums` of size `n`, return the majority element.

The majority element is the element that appears more than `⌊n / 2⌋` times. You may assume that the majority element always exists in the array.

#### Example 1
```plain
Input: nums = [3,2,3]
Output: 3
```

#### Example 2
```plain
Input: nums = [2,2,1,1,1,2,2]
Output: 2
``` 

#### Constraints

* `n == nums.length`.
* `1 <= n <= 5 * 10^4`.
* `-2^31 <= nums[i] <= 2^31 - 1`.
 

#### Follow-up: 
Could you solve the problem in linear time and in `O(1)` space?

### Solution 1: Counting the frequency

#### Code
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
```plain
Output:
3
2
```

#### Complexity
* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(n)`.

### Solution 2: Sorting and picking the middle element

#### Code
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
```plain
Output:
3
2
```

#### Complexity
* Runtime: `O(nlogn)`, where `n = nums.length`.
* Extra space: `O(1)`.

### References
* [https://leetcode.com/problems/majority-element/](https://leetcode.com/problems/majority-element/)
* [https://www.leetsolve.com/169-majority-element](https://www.leetsolve.com/169-majority-element)