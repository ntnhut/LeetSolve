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
    //! @return true if the event can be added to the calendar successfully 
    //!         without causing an intersection.
    //! @param start, end  of the event you want to book
    //! @author Nhut Nguyen
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