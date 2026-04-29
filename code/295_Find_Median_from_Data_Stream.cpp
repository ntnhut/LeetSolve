#include <set>
using namespace std;
class MedianFinder {
    private:
    multiset<int> arr;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        arr.insert(num);
    }
    
    double findMedian() {
        const int N = arr.size(); 
        int midIdx = N / 2;
        auto it = arr.begin();
        std::advance(it, midIdx);
        double median = *it;
        
        if (N % 2 == 1) {
            return median;
        } else {
            std::advance(it, -1);
            return (static_cast<double>(*it) + median) / 2.0;
        }
    }
};

int main() {

}