#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> _q;
    int _k;
public:
    KthLargest(int k, vector<int>& nums) : 
        _q(nums.begin(), nums.end()), _k(k) {
    }
    //! @brief  Appends the integer val to the queue and  
    //!         returns the k-th largest element in the stream
    //! @author Nhut Nguyen
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