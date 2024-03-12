# Kth Largest Element in a Stream
% Easy 
## Problem statement

[^url]Create a class that can find the `k-th` largest element in a stream of integers. This is the `k-th` largest element when the elements are arranged in sorted order, not the `k-th` distinct element.

The `KthLargest` class needs to support the following operations:

1. `KthLargest(int k, int[] nums)`: This initializes the object with an integer `k` and a stream of integers `nums`.
2. `int add(int val)`: This method adds the integer `val` to the stream and returns the element representing the `k-th` largest element in the stream. 

[^url]: https://leetcode.com/problems/kth-largest-element-in-a-stream/
### Example 1
```text
Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
``` 

### Constraints

* `1 <= k <= 10^4`.
* `0 <= nums.length <= 10^4`.
* `-10^4 <= nums[i] <= 10^4`.
* `-10^4 <= val <= 10^4`.
* At most `10^4` calls will be made to add.
* It is guaranteed that there will be at least `k` elements in the array when you search for the `k-th` element.

## Solution 1: Sort and Append

Sort the stream when initialization. And keep it sorted whenever you append a new value.

### Example 1
For `nums = [4, 5, 8, 2]` and `k = 3`.
* Sort `nums = [8, 5, 4, 2]`.
* Adding `3` to `nums`. It becomes `[8, 5, 4, 3, 2]`. The third largest element is `4`.
* Adding `5` to `nums`. It becomes `[8, 5, 5, 4, 3, 2]`. The third largest element is `5`. 
* Adding `10` to `nums`. It becomes `[10, 8, 5, 5, 4, 3, 2]`. The third largest element is `5`.
* So on and so on.

### Code 
```cpp
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class KthLargest {
    vector<int> _nums;
    int _k;
public:
    KthLargest(int k, vector<int>& nums) : _nums(nums), _k(k) {   
        // sort the nums when constructed
        sort(_nums.begin(), _nums.end(), std::greater());
    }
    
    int add(int val) {
        auto it = _nums.begin();
        // find the position to insert val
        while (it != _nums.end() &&  val < *it) {
            it++;
        }
        _nums.insert(it, val);
        // return the k-th largest element
        return *(_nums.begin() + _k - 1);
    }
};
int main() {
    vector<int> nums{4,5,8,2};
    KthLargest a(3, nums);
    cout << a.add(3) << endl;
    cout << a.add(5) << endl;
    cout << a.add(10) << endl;
    cout << a.add(9) << endl;
    cout << a.add(4) << endl;
}
```
```text
Output:
4
5
5
8
8
```

This solution maintains a sorted vector `_nums` in non-ascending order upon initialization, which stores the elements. When adding a new element `val`, it inserts it into `_nums` while maintaining the sorted order. 

Since `_nums` is sorted in non-ascending order, the `k`-th largest element is always at index `_k - 1`. Thus, upon adding a new element, it returns the value at index `_k - 1` as the `k`-th largest element in the collection. 

This approach optimizes the `add` operation by leveraging the sorted nature of the data structure, resulting in efficient retrieval of the `k`-th largest element.

### Complexity

* Runtime: for the constructor `O(N*logN)`, where `N = nums.length`. For the `add` method, `O(N)`.
* Extra space: `O(1)`.

## Solution 2: Priority queue

There is a data structure that has the property you want in this problem. 

It is `std::priority_queue`, which keeps its top element is always the largest one according to the comparison you define for the queue.

By default, the "less than" comparison is used for {index}`std::priority_queue` (heap) and the top one is always the biggest element. 

If you want the top one is always the smallest element, you can use the comparison "greater than" for your heap.

### Code
```cpp
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> _q;
    int _k;
public:
    KthLargest(int k, vector<int>& nums)
    // create the heap when constructed 
    : _q(nums.begin(), nums.end()), _k(k) {

    }
    
    int add(int val) {
        _q.push(val);

        // remove elements until _q remains k elements
        while (_q.size() > _k) {
            _q.pop();
        }
        return _q.top();
    }
};
int main() {
    vector<int> nums{4,5,8,2};
    KthLargest a(3, nums);
    cout << a.add(3) << endl;
    cout << a.add(5) << endl;
    cout << a.add(10) << endl;
    cout << a.add(9) << endl;
    cout << a.add(4) << endl;
}
```
```text
Output:
4
5
5
8
8
```

### Complexity

* Runtime: for the constructor, `O(N*logN)`, where `N = nums.length`. For the `add` method, `O(logN)`.
* Extra space: `O(1)`.

## Conclusion

The key insight of Solution 2 is utilizing a min-heap (priority queue with the `greater` comparator) to find the kth largest element in a collection. 

Upon initialization, the constructor populates the priority queue with the elements from the input vector `nums`. When adding a new element `val`, it inserts it into the priority queue and then removes elements until the size of the priority queue is reduced to `_k`, ensuring that only the k largest elements are retained in the queue. 

Finally, it returns the top element of the priority queue, which represents the kth largest element. This approach leverages the properties of a min-heap to track the kth largest element in the collection, resulting in an overall efficient solution.

## Exercise
- Kth Largest Element in an Array[^ex].

[^ex]: https://leetcode.com/problems/kth-largest-element-in-an-array/