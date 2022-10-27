#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//! @param nums An array of n integers.
//! @return The majority element that appears more than n/2 times.
//! @note  Assume the majority element always exists in the array.
//! @author Nhut Nguyen
int majorityElement(vector<int>& nums) {
    const int mid = nums.size() / 2;    
    std::nth_element(nums.begin(), nums.begin() + mid, nums.end());
    return nums[mid];
}
int main() {
    vector<int> nums{3,2,3};
    cout << majorityElement(nums) << endl; // 3
    nums = {2,2,1,1,1,2,2};
    cout << majorityElement(nums) << endl; // 2
}