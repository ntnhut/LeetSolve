# My Calendar I


## [Problem statement](https://leetcode.com/problems/my-calendar-i/)

You're creating a program to use as your calendar. You can add new events to the calendar, but only if adding the event will not lead to a double booking.

A double booking occurs when two events have some time overlap, meaning there's a shared time period between them.

An event is represented as a pair of integers: `start` and `end`, which represent the booking on a half-open interval `[start, end)`. This interval includes all real numbers `x` such that `start <= x < end`.

You need to implement the `MyCalendar` class, which has the following functions:

1. `MyCalendar()`: Initializes the calendar object.
2. `boolean book(int start, int end)`: This function checks if the event with the given `start` and `end` can be added to the calendar without causing a double booking. If it's possible to add the event without a double booking, the function returns `true`. Otherwise, it returns `false`, and the event is not added to the calendar. 

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

### Code explanation

1. The private member `_events` is a vector of pairs, each representing an event with a start and end time.

2. The constructor `MyCalendar()` initializes an empty `_events` vector when an instance of the class is created.

3. The `book` method is used to book events. It takes two integers, `start` and `end`, representing the start and end times of the event to be booked.

4. Inside the `book` method, there's a loop that iterates through the `_events` vector. For each existing event represented by `e`, it checks if there is any overlap between the new event (given by `start` and `end`) and the existing event. If any overlap is detected, it returns `false`, indicating that the booking is impossible.

5. If there is no overlap with any existing events, the new event (represented by the pair `{start, end}`) is added to the `_events` vector, and the method returns `true` to indicate a successful booking.

This code essentially maintains a list of events and checks for overlaps when booking a new event. If no overlaps are found, it adds the new event to the list and allows the booking.

### Complexity
For the `book` method:
* Runtime: `O(n)`, where `n`= `_events.length`.
* Extra space: `O(1)`.

## Solution 2: Set

Since the events have no intersection, they can be sorted. You can also consider two events to be the same if they intersect.

With that in mind, you can use {index}`std::set`[](https://en.cppreference.com/w/cpp/container/set) to store the sorted unique events.

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

### Code explanation

1. The `Event` type is defined as a pair of integers representing an event's start and end times.

2. The `EventCmp` struct defines a custom comparison function for events. It compares events based on their end times. If the end time of one event is less than or equal to the start time of another event, they are considered non-overlapping.

3. The `MyCalendar` class maintains a set `_events` of events sorted according to the custom comparator. This ensures that the events are ordered by their end times for efficient overlap checking.

4. The `book` method takes two integers, `start` and `end`, representing the start and end times of a new event.

5. Inside the `book` method, the code attempts to insert the new event into the `_events` set using `_events.insert({start, end})`. The `insert` function returns a pair of iterators and a boolean. The boolean indicates whether the insertion was successful or not.

6. If the insertion is successful (i.e., the event does not overlap with any existing events), the method returns `true`, indicating that the event has been booked.

### Complexity

This solution efficiently handles event bookings by maintaining a sorted set of events based on their end times, allowing for quick overlap checks when booking new events. It has a time complexity of `O(logn)` for each booking operation, where `n` is the number of events already booked.

For the `book` method:
* Runtime: `O(logn)`, where `n = _events.length`.
* Extra space: `O(1)`.
