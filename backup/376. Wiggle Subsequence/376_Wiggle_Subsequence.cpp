#include <iostream>
#include <vector>
using namespace std;
//! @return the length of the longest wiggle subsequence of nums
//! @param nums an array of non-negative integers
//! @author Nhut Nguyen
int wiggleMaxLength(vector<int>& nums) {
    // nums[0] is always the first extremum
    // start to find the second extremum
    int i = 1;
    while (i < nums.size() && nums[i] == nums[i - 1]) {
        i++;
    }
    if (i == nums.size()) {
        // all nums[i] are equal
        return 1;
    }
    int sign = nums[i] > nums[i - 1] ? 1 : -1;
    int count = 2;
    i++;
    while (i < nums.size()) {
        if ((nums[i] - nums[i - 1]) * sign < 0) {
            // nums[i] is an extremum
            count++;
            sign = -sign;
        }
        i++;
    }
    return count;
}
int main() {
    vector<int> nums{1,7,4,9,2,5};
    cout << wiggleMaxLength(nums) << endl;
    nums = {1,17,5,10,13,15,10,5,16,8};
    cout << wiggleMaxLength(nums) << endl;
    nums = {1,2,3,4,5,6,7,8,9};
    cout << wiggleMaxLength(nums) << endl;
}