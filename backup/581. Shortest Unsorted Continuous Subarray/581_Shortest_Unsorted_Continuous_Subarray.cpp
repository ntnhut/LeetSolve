#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//! @return the length of the shortest subarray that if you sort it
//!         in ascending order, the whole array is also sorted.
//! @param nums an array of integers
//! @author Nhut Nguyen
int findUnsortedSubarray(vector<int>& nums) {
    const int n = nums.size();
    int right = 0;
    int max = nums[0];
    for (int i = 0; i < nums.size(); i++) {
        if (max > nums[i]) {
            right = i;
        } else {
            max = nums[i];
        }
    }
    int left = 0;
    int min = nums[n - 1];
    for (int i = n - 1; i >= 0; i--) {
        if (min < nums[i]) {
            left = i;
        } else {
            min = nums[i];
        }
    }
    return left >= right ? 0 : right - left + 1;
}
int main() {
    vector<int> nums{2,6,4,8,10,9,15};
    cout << findUnsortedSubarray(nums) << endl;
    nums = {1,2,3,4};
    cout << findUnsortedSubarray(nums) << endl;
    nums = {1};
    cout << findUnsortedSubarray(nums) << endl;
}