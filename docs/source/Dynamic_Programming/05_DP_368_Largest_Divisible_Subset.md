# Largest Divisible Subset

## [Problem statement](https://leetcode.com/problems/largest-divisible-subset/)

You have a collection of positive integers called `nums`, where each integer is distinct. Your task is to find the largest subset `answer` from this collection, such that for every pair of elements `(answer[i], answer[j])` within this subset:

* Either `answer[i]` is a multiple of `answer[j]` (i.e., `answer[i] % answer[j] == 0`), or
* `answer[j]` is a multiple of `answer[i]` (i.e., `answer[j] % answer[i] == 0`).

If there are multiple possible solutions, you can return any of them.

### Example 1
```text
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.
```

### Example 2
```text
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
```

### Constraints

* `1 <= nums.length <= 1000`.
* `1 <= nums[i] <= 2 * 10^9`.
* All the integers in `nums` are **unique**.

## Solution 1: Bruteforce with Dynamic programming

Note that the condition `a % b == 0` is called *`a` is divisible by `b`*. In mathematics, it can also be called *`b` divides `a`* and be written as `b | a`.

The symmetry of the divisibility criteria means it does not count the ordering of the `answer`. You could sort the vector `nums` before trying to find the longest subset `answer = [answer[0], answer[1], ..., answer[m]]` where `answer[i] | answer[j]` with all `0 <= i <= j <= m`.

Now assuming the `nums` were sorted. For each `i`, you need to find the largest subset `maxSubset[i]` starting from `nums[i]`. And the final answer is the largest one among them. 

### Example 3
```text
Input: nums = [2, 4, 3, 9, 8].
Sorted nums = [2, 3, 4, 8, 9]. 
maxSubset[0] = [2, 4, 8].
maxSubset[1] = [3, 9].
maxSubset[2] = [4, 8].
maxSubset[3] = [8].
maxSubset[4] = [9].
Output: [2, 4, 8].
```

Note that for a sorted `nums`, if `nums[i] | nums[j]` for some `i < j`, then `maxSubset[j]` is a subset of `maxSubset[i]`. 

For example, `maxSubset[2]` is a subset of `maxSubset[0]` in Example 3 because `nums[0] = 2 | 4 = nums[2]`.

That might lead to some unnecessary recomputing. To avoid it, you could use *dynamic programming* to store the `maxSubset[j]` you have already computed.

### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//! @brief compute the maxSubset[i] starting from nums[i] 
//!         and store it to _map[i]
//! @note nums is sorted
vector<int> largestDivisibleSubsetOf(vector<int>& nums, int i, 
                                    unordered_map<int, vector<int> >& _map) {

    if (_map.find(i) != _map.end()) {
        return _map[i];
    }
    vector<int> maxSubset{nums[i]};
    if (i == nums.size() - 1) {
        _map.insert({i, maxSubset});
        return maxSubset;
    }
    for (int j = i + 1; j < nums.size(); j++) {
        if (nums[j] % nums[i] == 0) {
            auto subset = largestDivisibleSubsetOf(nums, j, _map);
            subset.push_back(nums[i]);
            if (maxSubset.size() < subset.size()) {
                maxSubset = subset;
            }
        }
    }
    _map.insert({i, maxSubset});
    return maxSubset;
}
vector<int> largestDivisibleSubset(vector<int>& nums) {
    if (nums.size() <= 1) {
        return nums; 
    } 
    unordered_map<int, vector<int> > _map;
    sort(nums.begin(), nums.end());
    vector<int> answer;
    for (int i = 0; i < nums.size(); i++) {
        auto maxSubset = largestDivisibleSubsetOf(nums, i, _map);
        if (answer.size() < maxSubset.size()) {
            answer = maxSubset;
        }
    }
    return answer;        
}
void printSolution(vector<int>& result) {
    cout << "[";
    for (auto& v : result) {
        cout << v << ",";
    }
    cout << "]" << endl;
}
int main() {
    vector<int> nums{2,1,3};
    auto answer = largestDivisibleSubset(nums);
    printSolution(answer);
    nums = {1,2,4,8};
    answer = largestDivisibleSubset(nums);
    printSolution(answer);
}
```
```text
Output:
[2,1,]
[8,4,2,1,]
```

### Complexity
* Runtime: $O(2^N)$, where $N$ is `nums.length`.
* Extra space: $O(N^2)$.

## Solution 2: Store only the representative of the `maxSubset`
In the brute-force solution above, you used a big `map` to log all `maxSubset[i]` though you need only the largest one at the end.

One way to save memory (and eventually improve performance) is just storing the representative of the chain relationship between the values `nums[i]` of the `maxSubset` through their indices mapping. 

That means if `maxSubset[i] = [nums[i0] | nums[i1] | ... | nums[iN1]] | nums[iN]]`, you could log `pre[iN] = iN1`, ...,  `prev[i1] = i0`. 

Then all you need to find is only the last index `iN` of the largest `maxSubset`. 

### Example 3
```text
Input: nums = [2, 4, 3, 9, 8].
sorted nums = [2, 3, 4, 8, 9]. 
pre[0] = -1 (there is no nums[i] | nums[0]).
pre[1] = -1 (there is no nums[i] | nums[1]).
pre[2] = 0 (nums[0] is the only divisor of nums[2]).
pre[3] = 2 (for the largest subset though nums[0] and nums[2] are both divisors of nums[3]). 
pre[4] = 1 (nums[1] is the only divisor of nums[4]).
iN = 3 ([2 | 4 | 8] is the largest maxSubset).
Output: [8, 4, 2].
```

### Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> largestDivisibleSubset(vector<int>& nums) {
    if (nums.size() <= 1) {
        return nums; 
    }
    sort(nums.begin(), nums.end());
    int maxSize = 0;    // the size of the resulting subset
    int maxindex = 0;   // nums[maxindex] is the largest value of the resulting subset
    vector<int> subsetSize(nums.size(), 1); // subsetSize[i] stores the size 
                                            // of the largest subset having 
                                            // biggest number nums[i]
    vector<int> pre(nums.size(), -1);       // pre[i] stores the previous 
                                            // index of i in their largest subset
    for (int i = 0; i < nums.size(); i++) {
        // find the previous nums[j] that make subsetSize[i] largest
        for (int j = i - 1; j >= 0; j--) {

            if (nums[i] % nums[j] == 0 && subsetSize[j] + 1 > subsetSize[i]) {
                subsetSize[i] = subsetSize[j] + 1;
                pre[i] = j;
            }
        }
        // update the largest subset
        if (maxSize < subsetSize[i]) {
            maxSize = subsetSize[i];
            maxindex = i;
        }
    }
    vector<int> result;
    while (maxindex != -1) {
        result.push_back(nums[maxindex]);
        maxindex = pre[maxindex];
    }
    return result;        
}
void printSolution(vector<int>& result) {
    cout << "[";
    for (auto& v : result) {
        cout << v << ",";
    }
    cout << "]" << endl;
}
int main() {
    vector<int> nums{2,1,3};
    auto result = largestDivisibleSubset(nums);
    printSolution(result);
    nums = {1,2,4,8};
    result = largestDivisibleSubset(nums);
    printSolution(result);
}
```
```text
Output:
[2,1,]
[8,4,2,1,]
```

### Complexity
* Runtime: $O(N^2)$, where $N$ is `nums.length`.
* Extra space: $O(N)$.

## Key takeaway
In this interesting problem, we use index mapping to simplify everything. That improves the performance in both runtime and memory.


