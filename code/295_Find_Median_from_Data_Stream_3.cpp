#include <set>
#include <iostream>
using namespace std;
class MedianFinder {
    private:
    multiset<int> arr;
    multiset<int>::iterator medIt;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        arr.insert(num);
        if (arr.size() == 1) {
            medIt = arr.begin();
        } else if (arr.size() % 2 == 0 && num > *medIt) {
            medIt++;
        }
    }
    
    double findMedian() {
        double median = *medIt;
        
        if (arr.size() % 2 == 1) {
            return median;
        } else {
            return (median + *std::prev(medIt)) / 2.0;
        }
    }
};

int main() {
    MedianFinder obj;
    obj.addNum(10);
    cout << obj.findMedian() << endl;
    obj.addNum(50);
    cout << obj.findMedian() << endl;
    obj.addNum(30);
    cout << obj.findMedian() << endl;
    obj.addNum(40);
    cout << obj.findMedian() << endl;
    obj.addNum(20);
    cout << obj.findMedian() << endl;
    return 0;
}