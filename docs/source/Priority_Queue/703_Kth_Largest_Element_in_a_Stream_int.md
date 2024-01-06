# Kth Largest Element in a Stream

## [Problem statement](https://leetcode.com/problems/kth-largest-element-in-a-stream/)

Create a class that can find the `k-th` largest element in a stream of integers. This is the `k-th` largest element when the elements are arranged in sorted order, not the `k-th` distinct element.

The `KthLargest` class needs to support the following operations:

1. `KthLargest(int k, int[] nums)`: This initializes the object with an integer `k` and a stream of integers `nums`.
2. `int add(int val)`: This method adds the integer `val` to the stream and returns the element representing the `k-th` largest element in the stream. 

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
        sort(_nums.begin(), _nums.end(), std::greater());
    }
    
    int add(int val) {
        auto it = _nums.begin();
        while (it != _nums.end() &&  val < *it) {
            it++;
        }
        _nums.insert(it, val);
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

### Code explanation

1. The constructor takes two parameters, `k` and `nums`, where `k` is the target `k`-th largest value, and `nums` is the initial vector of integers. Inside the constructor, it sorts the `_nums` vector in non-ascending order using `std::greater()` as the comparison function. This ensures that the largest elements are at the beginning of the vector, making it easier to find the `k`-th largest element later.

2. The `add` method takes an integer `val` as its parameter, representing the value to be added to the collection. It inserts `val` into the `_nums` vector while maintaining the sorted order. It uses an iterator `it` to traverse the vector until it finds the correct position to insert `val`. After inserting `val`, the method returns the `k`-th largest element, which is now located at the `_k - 1` index in the sorted vector.

Here's how the `KthLargest` class works:

- When you create an instance of `KthLargest`, it sorts the initial `nums` vector in non-ascending order.
- When you call the `add` method with a new integer, it inserts the integer into the sorted `_nums` vector while keeping it sorted.
- After each insertion, the method returns the `k`-th largest element from the sorted vector.

This implementation allows you to efficiently find the `k`-th largest element in the collection with each `add` operation, as the vector is maintained in a sorted order.


### Complexity
The time complexity of adding an element in this implementation is `O(N)`, where `N` is the number of elements in the vector. However, finding the `k`-th largest element (after adding) is an `O(1)` operation, as you are directly accessing the `k`-th largest element from the sorted vector.

* Runtime: for the constructor `O(N*logN)`, where `N = nums.length`. For the `add` method, `O(N)`.
* Extra space: `O(1)`.

## Solution 2: Priority queue

There is a data structure that has the property you want in this problem. 

It is [`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue), which keeps its top element is always the largest one according to the comparison you define for the queue.

By default, the "less than" comparison is used for {index}`std::priority_queue` and the top one is always the biggest element. 

If you want the top one is always the smallest element, you can use the comparison "greater than" for your queue.

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
    : _q(nums.begin(), nums.end()), _k(k) {

    }
    
    int add(int val) {
        _q.push(val);
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

### Code explanation

1. The constructor takes two parameters, `k` and `nums`, where `k` is the target `k`-th largest value, and `nums` is the initial vector of integers. Inside the constructor, it initializes a `priority_queue` `_q` using the elements from the `nums` vector. This priority queue is configured to store elements in ascending order, so the smallest elements will be at the top of the queue.

2. The `add` method takes an integer `val` as its parameter, representing the value to be added to the collection. It pushes `val` onto the priority queue `_q`, which maintains the elements in ascending order. Then, it checks the size of the priority queue. If the size exceeds `_k`, it pops elements from the front of the priority queue until the size is reduced to `_k`. Finally, it returns the top element of the priority queue, which is the `k`-th largest element in the collection.

Here's how the `KthLargest` class works:

- When you create an instance of `KthLargest`, it initializes a priority queue with the elements from the `nums` vector, ensuring that the smallest elements are at the top of the queue.

- When you call the `add` method with a new integer, it pushes the integer onto the priority queue, maintaining the ascending order.

- After each insertion, the method checks the size of the priority queue. If the size exceeds `_k`, it removes elements from the front of the queue until the size is reduced to `_k`.

- Finally, the method returns the top element of the priority queue, which is the `k`-th largest element in the collection.

This implementation allows you to efficiently find the `k`-th largest element in the collection with each `add` operation, as the priority queue is maintained in ascending order, and unnecessary elements are removed to keep the size at `_k`.


### Complexity
The time complexity of adding an element is `O(logN)`, where `N` is the number of elements in the priority queue. Finding the `k`-th largest element (after adding) is an `O(1)` operation, as you are directly accessing the top element of the priority queue.

* Runtime: for the constructor, `O(N*logN)`, where `N = nums.length`. For the `add` method, `O(logN)`.
* Extra space: `O(1)`.
