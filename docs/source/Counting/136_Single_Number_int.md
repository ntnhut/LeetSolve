# Single Number

## [Problem statement](https://leetcode.com/problems/single-number/)

You're provided with a non-empty array of integers called `nums`. In this array, every element occurs twice except for one element that appears only once. Your task is to identify and find that unique element.

To solve this problem, your solution needs to have a linear runtime complexity and utilize only a constant amount of extra space.

### Example 1

```text
Input: nums = [2,2,1]
Output: 1
```

### Example 2
```text
Input: nums = [4,1,2,1,2]
Output: 4
```
### Example 3
```text
Input: nums = [1]
Output: 1
``` 

### Constraints

* `1 <= nums.length <= 3 * 10^4`.
* `-3 * 10^4 <= nums[i] <= 3 * 10^4`.
* Each element in the array appears twice except for one element which appears only once.

## Solution 1: Counting the appearances
Count how many times each element appears in the array. Then return the one appearing only once.

### Code

```cpp
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
int singleNumber(vector<int>& nums) {
    unordered_map<int, int> count;
    for (int n : nums) {
        count[n]++;
    }
    int single;
    for (auto& pair : count) {
        if (pair.second == 1) {
            single = pair.first;
            break;
        }
    }
    return single;
}
int main() {
    vector<int> nums{2,2,1};
    cout << singleNumber(nums) << endl;
    nums = {4,1,2,1,2};
    cout << singleNumber(nums) << endl;
    nums = {1};
    cout << singleNumber(nums) << endl;
}
```
```text
Output:
1
4
1
```
This solution effectively finds the single number by counting the occurrences of each element in the array and selecting the one with a count of 1.

### Complexity

* Runtime: `O(N)`.
* Extra space: `O(N)`.

## Solution 2: Bitwise exclusive OR

You can also use the {index}`bitwise XOR` operator to cancel out the duplicated elements in the array. The remain element is the single one.

```text
a XOR a = 0.
a XOR 0 = a.
```

### Code

```cpp
#include <vector>
#include <iostream>
using namespace std;
int singleNumber(vector<int>& nums) {
    int single = 0;
    for (int n : nums) {
        single ^= n;
    }
    return single;
}
int main() {
    vector<int> nums{2,2,1};
    cout << singleNumber(nums) << endl;
    nums = {4,1,2,1,2};
    cout << singleNumber(nums) << endl;
    nums = {1};
    cout << singleNumber(nums) << endl;
}
```
```text
Output:
1
4
1
```
This solution utilizes bitwise XOR operation to efficiently find the single number that appears only once in the given array of numbers. By iteratively XOR-ing all the numbers in the array, the operation cancels out the duplicate numbers, leaving only the single number in the end. 

This approach optimizes the computation by leveraging the properties of bitwise XOR operation, which efficiently eliminates duplicates and isolates the single number in the array.

### Complexity

* Runtime: `O(N)`.
* Extra space: `O(1)`.
