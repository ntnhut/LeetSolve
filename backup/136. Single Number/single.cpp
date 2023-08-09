#include <vector>
#include <iostream>
using namespace std;

//! @param nums A vector of integers, each appears twice except one.
//! @return the single element.
//! @author Nhut Nguyen
int singleNumber(vector<int>& nums) {
    int single = 0;
    for (int n : nums) {
        single ^= n;
    }
    return single;
}


int main() {
    vector<int> nums{2,2,1};
    cout << singleNumber(nums) << endl; // 1
    nums = {4,1,2,1,2};
    cout << singleNumber(nums) << endl; // 4
    nums = {1};
    cout << singleNumber(nums) << endl; // 1
}
