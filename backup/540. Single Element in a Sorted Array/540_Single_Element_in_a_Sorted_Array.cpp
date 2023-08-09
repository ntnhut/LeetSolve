#include <vector>
#include <iostream>
using namespace std;

//! @return the single element that appears only once.
//! @param nums a sorted array of non-negative integers 
//!         where every element appears exactly twice, 
//!         except for one element which appears exactly once.
//! @author Nhut Nguyen
int singleNonDuplicate(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        int mid = (right + left)/4 * 2;
        if (nums[mid] != nums[mid + 1]) {
            right = mid;
        } else {
            left = mid + 2;
        }
    }
    return nums[right];
}

int  main() {
    vector<int> nums{1,1,2,3,3,4,4,8,8};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3,3,7,7,10,11,11};
    cout << singleNonDuplicate(nums) << endl;
    nums = {3};
    cout << singleNonDuplicate(nums) << endl;
}