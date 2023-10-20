# Subsets

## [Problem Statement](https://leetcode.com/problems/subsets/)
Given an integer array `nums` of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

### Example 1
```text
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

### Example 2
```text
Input: nums = [1]
Output: [[],[1]]
```

### Constraints

* `1 <= nums.length <= 10`.
* `-10 <= nums[i] <= 10`.
* All the numbers of `nums` are unique..

## Solution
You might need to find the relationship between the result of the array `nums` with the result of itself without the last element.

### Example 3
```text
Input: nums = [1,2]
Output: [[],[1],[2],[1,2]]
```
You can see the powerset of Example 3 was obtained from the one in Example 2 with additional subsets `[2]`, `[1,2]`. These new subsets were constructed from subsets `[]`, `[1]` of Example 2 appended with the new element `2`. 

Similarly, the powerset of Example 1 was obtained from the one in Example 3 with the additional subsets `[3]`, `[1,3]`, `[2,3]`, `[1,2,3]`. These new subsets were constructed from the ones of Example 3 appended with the new element `3`.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<vector<int>> subsets(vector<int>& nums) 
{
    vector<vector<int>> powerset = {{}};
    int i = 0;
    while (i < nums.size()) 
    {
        vector<vector<int>> newSubsets;
        for (auto subset : powerset) 
        {
            subset.push_back(nums[i]);  
            newSubsets.push_back(subset);
        }
        powerset.insert(powerset.end(), newSubsets.begin(), newSubsets.end());
        i++;
    }
    return powerset;
}
void print(vector<vector<int>>& powerset) 
{
    for (auto& set : powerset ) 
    {
        cout << "[";
        for (auto& element : set) 
        {
            cout << element << ",";
        }
        cout << "]";
    }
    cout << endl;
}
int main() 
{
    vector<int> nums{1,2,3};
    auto powerset = subsets(nums);
    print(powerset);
    nums = {1};
    powerset = subsets(nums);
    print(powerset);
}
```
```text
Output:
[][1,][2,][1,2,][3,][1,3,][2,3,][1,2,3,]
[][1,]
```

### Code explanation

1. The code initializes an empty vector of vectors called `powerset` to store the subsets. It starts with an initial subset containing an empty vector, representing the empty set: `{{}}`.

2. Within the loop, it creates a new vector of vectors called `newSubsets` to store subsets that include the `i`-th element of `nums`.

3. It iterates through the existing subsets in `powerset`. For each subset, it creates a copy of it (represented by the `subset` variable), adds the `i`-th element from `nums` to the copied subset, and pushes the modified subset into the `newSubsets` vector.

4. After processing all existing subsets, the code adds the contents of `newSubsets` to the `powerset` vector. This effectively combines the current subsets with subsets that include the `i`-th element of `nums`.

5. It repeats steps 2-4 until all elements in `nums` have been considered.

6. Finally, the code returns the `powerset`, which now contains all possible subsets of `nums`.

### Complexity
This code essentially generates subsets by iteratively adding each element of `nums` to the existing subsets and accumulating the results. The time complexity of this code is `O(2^N)`, where `N` is the number of elements in `nums`, as it generates all possible subsets. The space complexity is also `O(2^N)` due to the space required to store the subsets.

* Runtime: `O(2^N)`.
* Extra space: `O(2^N)`.



