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