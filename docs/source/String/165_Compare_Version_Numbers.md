# Compare Version Numbers
% Medium
## Problem statement
 
[^url]Given two version numbers, `version1` and `version2`, your task is to compare them.

Version numbers consist of one or more revisions joined by a dot `'.'`. Each revision is composed of digits and may contain leading zeros. Each revision has at least one character. Revisions are indexed from left to right, with the leftmost revision being revision 0, the next revision being revision 1, and so on.

For instance, `2.5.33` and `0.1` are valid version numbers.

To compare version numbers, you should compare their revisions in left-to-right order. Revisions are compared using their integer value, ignoring any leading zeros. This means that revisions `1` and `001` are considered equal. If a version number does not specify a revision at a particular index, treat that revision as `0`. For example, version `1.0` is less than version `1.1` because their revision 0s are the same, but their revision 1s are `0` and `1` respectively, and `0` is less than `1`.

The function should return the following:

* If `version1` is less than `version2`, return `-1`.
* If `version1` is greater than `version2`, return `1`.
* If `version1` and `version2` are equal, return `0`. 

[^url]: https://leetcode.com/problems/compare-version-numbers/
### Example 1
```text
Input: version1 = "1.01", version2 = "1.001"
Output: 0
Explanation: Ignoring leading zeroes, both "01" and "001" represent the same integer "1".
```

### Example 2
```text
Input: version1 = "1.0", version2 = "1.0.0"
Output: 0
Explanation: version1 does not specify revision 2, which means it is treated as "0".
```

### Example 3
```text
Input: version1 = "0.1", version2 = "1.1"
Output: -1
Explanation: version1's revision 0 is "0", while version2's revision 0 is "1". 0 < 1, so version1 < version2.
``` 

### Constraints

* `1 <= version1.length, version2.length <= 500`.
* `version1` and `version2` only contain digits and `'.'`.
* `version1` and `version2` are valid version numbers.
* All the given revisions in `version1` and `version2` can be stored in a 32-bit integer.

## Solution
Each version can be considered as an array of revisions.

```text
version = revisions[0].revisions[1].revisions[2]....
```
The problem is to compare each `revisions[i]` between two versions.

For example, `revisions[0]` of `version1` is less than of `version2` in Example 3. So the result is `-1`.

All `revisions[i]` of `version1` and `version2` are equal in Example 1. So the result is `0`.

The number of revisions between the versions might not be equal (like in Example 2). 

If all revisions of the shorter version are equal to the corresponding revisions of the longer one, the version having extra revisions and there exists a non-zero revision among them is the bigger one. Otherwise, the two versions are equal.

### Code

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
vector<int> toVector(const string& version) {
    vector<int> revisions;
    string revision;
    for (char c : version) {
        if (c != '.') {
            revision += c;
        } else {
            revisions.push_back(stoi(revision));
            revision = "";
        }
    }
    revisions.push_back(stoi(revision));
    return revisions;
}

int compareVersion(string version1, string version2) { 
    vector<int> r1 = toVector(version1);    
    vector<int> r2 = toVector(version2);

    int i = 0;
    while (i < r1.size() && i < r2.size()) {
        if (r1[i] < r2[i]) {
            return -1;
        } else if (r1[i] > r2[i]) {
            return 1;
        }
        i++;
    }
    int remain1 = accumulate(r1.begin() + i, r1.end(), 0);
    int remain2 = accumulate(r2.begin() + i, r2.end(), 0);
    if (remain1 < remain2) {
        return -1;
    } else if (remain1 > remain2) {
        return 1;
    }
    return 0;
}
int main() {
    cout << compareVersion("1.01", "1.001") << endl;
    cout << compareVersion("1.0", "1.0.0") << endl;
    cout << compareVersion("0.1", "1.1") << endl;
}
```
```text
Output:
0
0
-1
```

This solution first converts the version strings into vectors of integers representing the individual components of the version numbers. This conversion is done by iterating through each character of the version string, accumulating digits until encountering a dot, at which point the accumulated integer is added to the revisions vector. 

Once both version strings are converted into vectors, the function iterates through the vectors, comparing corresponding elements to determine the relationship between the versions. Additionally, it accounts for any remaining digits in the longer version string after the common components by summing them up and comparing the totals. 

This approach simplifies the comparison process by breaking down the version strings into easily comparable components.

### Complexity
* Runtime: `O(N)` where `N = max(version1.length, version2.length)`.
* Extra space: `O(N)`.

## C++ Notes
* [`std::stoi(string)`](https://en.cppreference.com/w/cpp/string/basic_string/stol) is used to convert a `string` to an `int`. It ignores the leading zeros for you.
* [`std::accumulate(firstIter, lastIter, initValue)`](https://en.cppreference.com/w/cpp/algorithm/accumulate) is used to compute the sum of a container. 


