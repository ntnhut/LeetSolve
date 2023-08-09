#include <vector>
#include <iostream>
using namespace std;

//! @brief find the subarray having the largest sum
//! @param nums a vector of integers
//! @author Nhut Nguyen
int maxSubArray(vector<int>& nums) {
    int maxSum = -10000;
    int currSum = 0;
    for (auto& num : nums) {
        currSum = currSum < 0 ? num : currSum + num;
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maxSubArray(nums) << endl; // 6
    nums = {1};
    cout << maxSubArray(nums) << endl;
    nums = {5,4,-1,7,8};
    cout << maxSubArray(nums) << endl; // 23
}