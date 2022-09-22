#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//! @param nums An array of n integers.
//! @return The element that appears more than n/2 times.
//! @author Nhut Nguyen
int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size()/2];
}
int main() {
    vector<int> nums{3,2,3};
    cout << majorityElement(nums) << endl; // 3
    nums = {2,2,1,1,1,2,2};
    cout << majorityElement(nums) << endl; // 2
}