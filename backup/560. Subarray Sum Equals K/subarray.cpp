#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//! @return return the number of continuous subarrays of nums whose sum equals to k.
//! @author Nhut Nguyen
int subarraySum(vector<int>& nums, int k) {
    int count = 0;
    unordered_map<int, int> sums;
    int sumi = 0;
    for (int i = 0; i < nums.size(); i++) {
        sumi += nums[i];
        if (sumi == k) {
            count++;
        }
        auto it = sums.find(sumi - k);
        if (it != sums.end()) {
            count += it->second;
        }
        sums[sumi]++;
    }
    return count;
}
int main() {
    vector<int> nums{1,1,1};
    cout << subarraySum(nums, 2) << endl; // 2
    nums = {1,2,3};
    cout << subarraySum(nums, 3) << endl; // 2
    nums = {1,-1,0};
    cout << subarraySum(nums, 0) << endl; // 3
}