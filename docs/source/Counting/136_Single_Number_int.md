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
int singleNumber(vector<int>& nums) 
{
    unordered_map<int, int> count;
    for (int n : nums) {
        count[n]++;
    }
    int single;
    for (auto& pair : count) 
    {
        if (pair.second == 1) 
        {
            single = pair.first;
            break;
        }
    }
    return single;
}
int main() 
{
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

### Code explanation

1. The code initializes an {index}`unordered map` `count` where the keys are integers from `nums`, and the values represent the count of each integer's occurrence in the `nums` array.

2. It then iterates through the `nums` array. For each element `n` in `nums`, it increments the count for that element in the `count` map.

3. Next, it initializes an integer variable `single` which will store the single number we are looking for.

4. The loop goes through the `count` map. For each key-value pair in the map it checks if the count (the value in the pair) is equal to 1. If so, it means this is the number that appears only once, so it assigns that number to the `single` variable and breaks out of the loop.

5. Finally, it returns the `single` variable, which contains the single number that appears only once in the `nums` array.


### Complexity

This solution effectively finds the single number by counting the occurrences of each element in the array and selecting the one with a count of 1. It has a time complexity of `O(N)` because it iterates through the `nums` array once, and it uses additional memory to store the counts in the unordered map, resulting in a space complexity of `O(N)` in the worst case, where `N` is the number of elements in the `nums` array.

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
int singleNumber(vector<int>& nums) 
{
    int single = 0;
    for (int n : nums) 
    {
        single ^= n;
    }
    return single;
}
int main() 
{
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

### Code explanation

1. The code initializes an integer variable `single` to 0. This variable will be used to keep track of the single number we are looking for.

2. The loop then iterates through the `nums` array. For each element `n` in `nums`, it performs the `XOR` (`^`) operation on `single` and `n`. The `XOR` operation returns 1 if the bits being compared are different and 0 if they are the same.

3. The key insight here is that XORing the same number twice results in `0` (`A ^ A = 0`), so when XORing all elements in the array, the numbers that appear twice will effectively cancel each other out, leaving only the single number that appears once in `single`.

4. After iterating through all elements in `nums`, `single` will hold the value of the single number.

5. Finally, it returns the `single` variable, which contains the single number that appears only once in the `nums` array.

### Complexity

This solution is highly efficient and has a time complexity of `O(N)`, where `N` is the number of elements in the `nums` array, because it iterates through the array once. Additionally, it has a space complexity of `O(1)` because it uses a constant amount of extra space to store the `single` variable, regardless of the size of the input array.

* Runtime: `O(N)`.
* Extra space: `O(1)`.
