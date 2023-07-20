# My Calendar I


## [Problem statement](https://leetcode.com/problems/my-calendar-i/)
You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a double booking.

A double booking happens when two events have some non-empty intersection (i.e., some moment is common to both events.).

The event can be represented as a pair of integers `start` and `end` that represents a booking on the half-open interval `[start, end)`, the range of real numbers `x` such that `start <= x < end`.

Implement the `MyCalendar` class:

* `MyCalendar()` Initializes the calendar object.
* `boolean book(int start, int end)` Returns `true` if the event can be added to the calendar successfully without causing a double booking. Otherwise, return `false` and do not add the event to the calendar.
 

### Example 1
```text
Input
["MyCalendar", "book", "book", "book"]
[[], [10, 20], [15, 25], [20, 30]]
Output
[null, true, false, true]

Explanation
MyCalendar myCalendar = new MyCalendar();
myCalendar.book(10, 20); // return True
myCalendar.book(15, 25); // return False. It can not be booked because time 15 is already booked by another event.
myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.
``` 

### Constraints

* `0 <= start < end <= 10^9`.
* At most `1000` calls will be made to book.

## Solution 1: Vector

You can store the booked events in a vector and check the intersection condition whenever you add a new event.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
class MyCalendar {
    private:
    vector<pair<int,int>> _events;
public:
    MyCalendar() {}
    bool book(int start, int end) {
        for (auto& e : _events) {
            if (!(e.second <= start || end <= e.first)) {
                return false;
            }
        }
        _events.push_back({start, end});
        return true;
    }
};
int main() {
    MyCalendar c;
    std::cout << c.book(10, 20) << std::endl;
    std::cout << c.book(15, 25) << std::endl;
    std::cout << c.book(20, 30) << std::endl;
}
```
```text
Output:
1
0
1
```
### Complexity
* Runtime: $O(n)$, where $n$ is `_events.length`.
* Extra space: $O(n)$.

## Solution 2: Set

Since the events have no intersection, they can be sorted. You can also consider two events to be the same if they intersect.

With that in mind, you can use [`std::set`](https://en.cppreference.com/w/cpp/container/set) to store the sorted unique events.

### Code
```cpp
#include <iostream>
#include <set>
using namespace std;
using Event = pair<int,int>;
struct EventCmp {
    bool operator()(const Event& lhs, const Event& rhs) const { 
        return lhs.second <= rhs.first; 
    }
};
class MyCalendar {
    private:
    set<Event, EventCmp> _events;
public:
    MyCalendar() {}
    bool book(int start, int end) {
        auto result = _events.insert({start, end});
        return result.second;
    }
};
int main() {
    MyCalendar c;
    std::cout << c.book(10, 20) << std::endl;
    std::cout << c.book(15, 25) << std::endl;
    std::cout << c.book(20, 30) << std::endl;
}
```
```text
Output:
1
0
1
```
### Complexity
* Runtime: $O(\log n)$, where $n$ is `_events.length`.
* Extra space: $O(n)$.



