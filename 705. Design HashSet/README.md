## 705. Design HashSet
Tag: easy, data structure

### Problem statement

Design a HashSet without using any built-in hash table libraries.

Implement `MyHashSet` class:

* `void add(key)` Inserts the value `key` into the HashSet.
* `bool contains(key)` Returns whether the value `key` exists in the HashSet or not.
* `void remove(key)` Removes the value `key` in the HashSet. If `key` does not exist in the HashSet, do nothing.
 

#### Example 1
```plain
Input
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
Output
[null, null, null, true, false, null, true, null, false]

Explanation
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // return True
myHashSet.contains(3); // return False, (not found)
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // return True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // return False, (already removed)
```

#### Constraints

* `0 <= key <= 10^6`.
* At most `10^4` calls will be made to `add`, `remove`, and `contains`.

### Solution 1: Store the keys 

The simplest way is using a container to store the keys so you can identify if a key belongs to the HashSet or not.

#### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
class MyHashSet {
    vector<int> _v;
public:
    MyHashSet() {        
    }   
    void add(int key) {
        if (!contains(key)) {
            _v.push_back(key);
        }
    }    
    void remove(int key) {
        auto it = _v.begin();
        while (it != _v.end()) {
            if (*it == key) {
                _v.erase(it);
                return;
            } else {
                it++;
            }
        }
    }    
    bool contains(int key) {
        for (int a : _v) {
            if (a == key) {
                return true;
            }
        }
        return false;
    }
};
int main() {
    MyHashSet m;
    m.add(1);
    m.add(2);
    cout << m.contains(1) << endl;
    cout << m.contains(3) << endl;
    m.add(2);
    cout << m.contains(2) << endl;
    m.remove(2);
    cout << m.contains(2) << endl;
}
```
```plain
Output:
1
0
1
0
```

#### Complexity
* Runtime: `O(N)` for all methods, where `N` is the number of values in the HashSet.
* Extra space: `O(N)`.

### Solution 2: Marking the keys

In this problem, the HashSet does not have anything other than methods `add`, `remove` and `contains`, which only check whether a `key` exists in it or not.

With this purpose you can simply mark the keys without storing them.

#### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
class MyHashSet {
    vector<bool> _v;
public:
    MyHashSet() : _v(1000001, false){        
    }   
    void add(int key) {
        _v[key] = true;
    }    
    void remove(int key) {
        _v[key] = false;
    }    
    bool contains(int key) {
        return _v[key];
    }
};
int main() {
    MyHashSet m;
    m.add(1);
    m.add(2);
    cout << m.contains(1) << endl;
    cout << m.contains(3) << endl;
    m.add(2);
    cout << m.contains(2) << endl;
    m.remove(2);
    cout << m.contains(2) << endl;
}
```
```plain
Output:
1
0
1
0
```

#### Complexity
* Runtime: `O(1)`.
* Extra space: `O(1)`.

### References
* [https://leetcode.com/problems/design-hashset/](https://leetcode.com/problems/design-hashset/)
* [https://www.leetsolve.com/705-design-hashset](https://www.leetsolve.com/705-design-hashset)