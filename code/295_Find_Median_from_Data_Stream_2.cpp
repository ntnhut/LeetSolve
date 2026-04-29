#include <queue>
#include <vector>
#include <iostream>
using namespace std;
class MedianFinder {
    private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> arr, q;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        arr.push(num);
    }
    
    double findMedian() {
        int midIdx = arr.size() / 2;
        q = arr;
        while (q.size() > midIdx + 1) {
            q.pop();
        }
        double median = q.top();
        
        if (arr.size() % 2 == 1) {
            return median;
        } else {
            q.pop();
            return (median + q.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
int main() {
    MedianFinder obj;
    obj.addNum(1);
    obj.addNum(2);
    cout << obj.findMedian() << endl;
    obj.addNum(3);
    cout << obj.findMedian() << endl;
    return 0;
}