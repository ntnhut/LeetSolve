## 941. Valid Mountain Array
Tags: easy.

### Problem statement
Given an array of integers `arr`, return `true` if and only if it is a valid *mountain array*.

Recall that arr is a **mountain array** if and only if:

* `arr.length >= 3`
* There exists some `i` with `0 < i < arr.length - 1` such that:
  * `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
  * `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`

![Mountain array](941_hint_valid_mountain_array.png) 

#### Example 1
```plain
Input: arr = [2,1]
Output: false
```

#### Example 2
```plain
Input: arr = [3,5,5]
Output: false
```

#### Example 3
```plain
Input: arr = [0,3,2,1]
Output: true
``` 

#### Constraints

* `1 <= arr.length <= 10^4`.
* `0 <= arr[i] <= 10^4`.

### Solution

Following the conditions, we have the following implementation.

#### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
bool validMountainArray(vector<int>& arr) {
    if (arr.size() < 3) {
        return false;
    }
    const int N = arr.size() - 1;
    int i = 0;
    while (i < N && arr[i] < arr[i + 1]) {
        i++;
    }
    if (i == 0 || i == N) {
        return false;
    }
    while (i < N && arr[i] > arr[i + 1]) {
        i++;
    }
    return i == N;
}
int main() {
    vector<int> arr{2,1};
    cout << validMountainArray(arr) << endl;
    arr = {3,5,5};   
    cout << validMountainArray(arr) << endl;
    arr = {0,3,2,1};   
    cout << validMountainArray(arr) << endl;
    arr = {9,8,7,6,5,4,3,2,1,0};
    cout << validMountainArray(arr) << endl;
}
```
```plain
Output:
0
0
1
0
```

#### Complexity
* Runtime: `O(N)`, where `N = arr.length`.
* Extra space: `O(1)`.


***

*Thanks for reading. Feel free to share your thought about my content and check out my FREE book [10 Classic Coding Challenges](https://store.nhutnguyen.com/l/10_classic).*

*What is your approach? The problem was picked from [leetcode.com](https://leetcode.com/problems/valid-mountain-array/). You can submit your solution in any programming language and check the performance.*