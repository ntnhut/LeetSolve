# Subarray Sum Equals K

## [Problem Statement](https://leetcode.com/problems/subarray-sum-equals-k/)

You have an array of integers called `nums` and an integer `k`. Your task is to determine the count of contiguous subarrays within this array, where the sum of elements in each subarray is equal to the value of `k`.

### Example 1
```text
Input: nums = [1,1,1], k = 2
Output: 2
```
### Example 2
```text
Input: nums = [1,2,3], k = 3
Output: 2
``` 

### Constraints

* `1 <= nums.length <= 2 * 10^4`.
* `-1000 <= nums[i] <= 1000`.
* `-10^7 <= k <= 10^7`.

## Solution 1: Bruteforce

For each element, for all subarrays starting from it, choose the satisfied ones.

### Example 3
For `nums = [1, -1, 0]` and `k = 0`, you get `3` subarrays for the result:
* There are three subarrays starting from `1`, which are `[1]`, `[1, -1]`, and `[1, -1, 0]`. Only the last two are satisfied.
* There are two subarrays starting from `-1`, which are `[-1]` and `[-1, 0]`. None is satisfied.
* Only `[0]` is the subarray starting from `0`. It is satisfied.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            if (sum == k) {
                count++;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

### Code explanation

1. `count` is initialized to zero. This variable will be used to store the count of subarrays whose sum equals `k`.

2. The outer loop runs through each element of the `nums` array, starting from index `0`.

3. Inside the outer loop, the variable `sum` is initialized to zero. This variable will be used to keep track of the sum of the current subarray being considered.

4. The inner loop runs through subarrays starting from index `i`. It iterates through indices `j` from `i` to the end of the array.

5. Inside the inner loop, the code adds the current element `nums[j]` to the `sum`.

6. After adding the current element to `sum`, the code checks whether `sum` is equal to the target `k`. If they are equal, it means a subarray with a sum of `k` has been found, so the `count` is incremented.

7. The inner loop continues to iterate, considering different subarrays with different starting and ending points.

8. Once the inner loop finishes for a given starting index `i`, the outer loop moves to the next index, and the process repeats.

9. After both loops complete, the function returns the final value of `count`, which represents the total number of subarrays within the `nums` array that have a sum equal to the given target `k`.

In summary, this code employs a brute-force approach by considering all possible subarrays and checking whether their sum equals the target `k`. The time complexity of this solution is relatively high due to the nested loops, resulting in an inefficient algorithm for larger input sizes.

### Complexity
* Runtime: $O(n^2)$, where $n$ is `nums.length`.
* Extra space: $O(1)$.

## Solution 2: Prefix sum
In the solution above, many sums can be deducted from the previous ones.

### Example 4
For `nums = [1, 2, 3, 4]`. Assume the sum of the subarrays `[1], [1, 2], [1, 2, 3], [1, 2, 3, 4]` were computed in the first loop. Then the sum of any other subarray can be deducted from those values.
* `sum([2, 3]) = sum([1, 2, 3]) - sum([1])`.
* `sum([2, 3, 4]) = sum([1, 2, 3, 4]) - sum([1])`.
* `sum([3, 4]) = sum(1, 2, 3, 4) - sum(1, 2)`.

In general, assume you have computed the sum `sum[i]` for the subarray `[nums[0], nums[1], ..., nums[i]]` for all `0 <= i < nums.length`. Then the sum of the subarray `[nums[j], nums[j+1], ..., nums[i]]` for any `0 <=j <= i` can be computed as `sum[i] - sum[j]`.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
    vector<int> sum(nums.size());
    sum[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i-1] + nums[i];
    }
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (sum[i] == k) {
            count++;
        }
        for (int j = 0; j < i; j++) {
            if (sum[i] - sum[j] == k) {
                count++;
            }
        }
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

### Code explanation

1. A vector `sum` is created to store the prefix sum values. This vector will be used to store the sum of elements up to each index in the `nums` array.

2. The first element of `sum` is initialized with the value of the first element in the `nums` array.

3. A loop iterates through the rest of the elements in `nums`, and for each element, the prefix sum up to that element is calculated and stored in the `sum` vector.

4. The variable `count` is initialized to zero. This variable will be used to store the count of subarrays whose sum equals `k`.

5. Another loop iterates through each element in the `nums` array. Inside the loop, the code checks if the prefix sum `sum[i]` is equal to the target `k`. If they are equal, it means a subarray starting from the beginning of the array and ending at index `i` has a sum of `k`, so the `count` is incremented.

6. A nested loop iterates through all possible subarrays ending at index `i`. The variable `j` ranges from 0 to `i-1`. Inside this nested loop, the code checks if the difference between `sum[i]` and `sum[j]` is equal to the target `k`. If they are equal, it means a subarray starting from index `j+1` and ending at index `i` has a sum of `k`, so the `count` is incremented.

7. The two loops together cover all possible subarrays and calculate the count of subarrays with a sum equal to `k`.

8. Finally, the function returns the total count of subarrays with a sum equal to the given target `k`.

In summary, this code uses the concept of prefix sum to efficiently calculate the sum of subarrays. It then iterates through the array to find subarrays with a sum equal to `k`, and the nested loop helps in calculating the sum of various subarray ranges. The time complexity of this solution is improved compared to the brute-force approach.

### Complexity
* Runtime: $O(n^2)$, where $n$ is `nums.length`.
* Extra space: $O(n)$.

## Solution 3: Faster lookup

You can rewrite the condition `sum[i] - sum[j] == k` in the inner loop of the Solution 2 to `sum[i] - k == sum[j]`. 

Then that loop can rephrase to *"checking if `sum[i] - k` was already a value of **some** computed `sum[j]`"*. 

Now you can use an `unordered_map` to store the `sums` as indices for the fast lookup.

### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    unordered_map<int, int> sums;
    int sumi = 0;
    for (int i = 0; i < nums.size(); i++) {
        sumi += nums[i];
        if (sumi == k) {
            count++;
        }
        auto it = sums.find(sumi - k);
        if (it != sums.end()) {
            count += it->second;
        }
        sums[sumi]++;
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl;
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl;
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl;
}
```
```text
Output:
2
2
3
```

### Code explanation

1. The variable `count` is initialized to zero. This variable will store the count of subarrays whose sum equals `k`.

2. An unordered map `sums` is created. This map will store the frequencies of cumulative sums encountered so far.

3. The variable `sumi` is initialized to zero. This variable will keep track of the cumulative sum as we iterate through the array.

4. A loop iterates through each element in the `nums` array. Inside this loop, the code updates the `sumi` by adding the current element's value.

5. If the `sumi` equals the target `k`, it means a subarray starting from the beginning of the array and ending at the current index has a sum of `k`. Therefore, the `count` is incremented.

6. The code checks if the complement sum `sumi - k` exists in the `sums` map using the `find` function. If the complement sum exists in the map, it means there are subarrays that start somewhere before the current index and end at the current index, and their sum equals `k`. The count of such subarrays is added to the `count`.

7. The frequency of the current cumulative sum `sumi` is incremented in the `sums` map.

8. The two loops together cover all possible subarrays and calculate the count of subarrays with a sum equal to `k`.

9. Finally, the function returns the total count of subarrays with a sum equal to the given target `k`.

In summary, this improved code uses an unordered map to efficiently track the frequency of cumulative sums. It utilizes the concept of complement sums to identify subarrays with the desired sum and adds their counts to the overall count. This approach significantly improves the time complexity compared to the brute-force solution.

### Complexity
* Runtime: $O(n)$, where $n$ is `nums.length`.
* Extra space: $O(n)$.

