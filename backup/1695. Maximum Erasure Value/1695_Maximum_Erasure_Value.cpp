#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int maximumUniqueSubarray(vector<int>& nums) {
    vector<int> sum(nums.size(), 0);
    sum[0] = nums[0];    
    int maxSum = sum[0];
    unordered_map<int, int> position;
    position[nums[0]] = 0;
    int start = -1;
    for (int i = 1; i < nums.size(); i++) {
        sum[i] = sum[i - 1] + nums[i];
        if (position.find(nums[i]) != position.end()) {
            start = max(start, position[nums[i]]);
        }
        position[nums[i]] = i;
        maxSum = (start == -1) ? sum[i] : max(maxSum, sum[i] - sum[start]);
    }
    return maxSum;
}

int main() {
    vector<int> nums{4,2,4,5,6};
    cout << maximumUniqueSubarray(nums) << endl;
    nums = {5,2,1,2,5,2,1,2,5};
    cout << maximumUniqueSubarray(nums) << endl;
}