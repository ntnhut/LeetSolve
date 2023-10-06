# Majority Element

## [Problem statement](https://leetcode.com/problems/majority-element/)

You're given an array `nums` with a total of `n` elements. Your task is to find and return the majority element.

The majority element is the element that appears more frequently in the array than any other element, specifically, it appears more than `n / 2` times.

You can assume that the majority element always exists in the given array.

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

### Code explanation

1. The code initializes an unordered map `freq` to keep track of the frequency of each unique integer in the `nums` array. Also, it defines a constant `HALF` as half the size of the `nums` array. This value represents the threshold for an element to be considered a majority element.

2. It iterates through the `nums` array using a for-each loop, processing each integer `a`:

   * It increments the frequency count of integer `a` in the `freq` map by 1.

   * It checks if the frequency count of `a` in the `freq` map is greater than `HALF`. If it is, this means `a` appears more than n/2 times, and it returns `a` as the majority element.

3. If the loop completes without finding a majority element, it returns the first element of the `nums` array (assuming there is always a majority element present).

The code effectively counts the occurrences of each integer in the array and checks if any integer appears more than `n/2` times. If so, it returns that integer as the majority element; otherwise, it defaults to the first element of the array.


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

### Code explanation

1. The code sorts the `nums` vector in ascending order using the `sort` function. This step rearranges the elements so that identical elements are adjacent to each other.

2. After sorting, the majority element (if it exists) will be in the middle of the sorted vector because it appears more than `n/2` times, where `n` is the size of the vector.

3. It returns the element at the middle index of the sorted vector, which is `nums[nums.size() / 2]`. This element is the majority element.


### Complexity
This code leverages the property of a majority element, which guarantees that it occupies the middle position in the sorted list of elements. Sorting the array allows us to easily access this middle element. 

* Runtime: `O(n*logn)`, where `n = nums.length`.
* Extra space: `O(1)`.

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

### Code explanation

1. The code calculates the index `mid`, which represents the approximate middle index of the `nums` vector. This is done by dividing the size of the vector by 2.

2. It uses the `std::nth_element` function to rearrange the elements in the `nums` vector such that the element at index `mid` will be in its correct sorted position, and all elements before it will be less than or equal to it, while all elements after it will be greater than or equal to it.

3. It returns the element at index `mid`. This element is the majority element.

### Complexity
By using `std::nth_element`, the code avoids fully sorting the entire vector, which makes it more efficient. 

* Runtime: `O(n)`, where `n = nums.length`.
* Extra space: `O(1)`.


```{admonition} Modern C++ tips
:class: tip

In the code of Solution 3, the partial sorting algorithm [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element) will make sure for all indices `i` and `j` that satisfy `0 <= i <= mid <= j < nums.length`,

    nums[i] <= nums[mid] <= nums[j].

In other words, `nums[mid]` divides the array `nums` into two groups: all elements that are less than or equal to `nums[mid]` and the ones that are greater than or equal to `nums[mid]`. 

Those two groups are unsorted. That is why the algorithm is called *partial* sorting. 

```