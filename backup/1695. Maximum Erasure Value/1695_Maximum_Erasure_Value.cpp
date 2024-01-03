#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

//! @param nums an array of positive integers 
//! @return the highest possible sum of a subarray 
//!         having distinct elements of nums.
//! @author Nhut Nguyen
int maximumUniqueSubarray(vector<int>& nums) {
    vector<int> sum(nums.size(), 0);
    sum[0] = nums.at(0);
    int maxSum = sum.at(0);
    unordered_map<int, int> position;
    position[nums.at(0)] = 0;
    int start = -1;
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum.at(i - 1) + nums.at(i);
        auto it = position.find(nums.at(i));
        if (it != position.end()) {
            start = max(start, it->second);
            it->second = i;
        } else {
            position.insert({nums.at(i), i});
        }            
        if (start == -1) {
            maxSum = sum.at(i);
        } else {
            maxSum = max(maxSum, sum.at(i) - sum.at(start));
        }
    }
    return maxSum;
}

int main() {
    vector<int> nums{4,2,4,5,6};
    cout << maximumUniqueSubarray(nums) << endl;
    nums = {5,2,1,2,5,2,1,2,5};
    cout << maximumUniqueSubarray(nums) << endl;
}