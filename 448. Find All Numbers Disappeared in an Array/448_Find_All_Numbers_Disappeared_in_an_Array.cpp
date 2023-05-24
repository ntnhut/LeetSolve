#include <vector>
#include <iostream>
using namespace std;

//! @return all the integers in the range [1, n] that do not appear in nums.
//! @param nums an array of n integers where nums[i] is in the range [1, n].
//! @author Nhut Nguyen
vector<int> findDisappearedNumbers(vector<int>& nums) {
    int j;
    for (int i{0}; i < nums.size(); i++) {
        j = abs(nums[i]);
        nums[j - 1] = -abs(nums[j - 1]);
    }
    vector<int> result;
    for (int i{1}; i <= nums.size(); i++) {
        if (nums[i - 1] > 0) {
            result.push_back(i);
        }
    }
    return result;
}

void print(vector<int>& nums) {
    cout << "[";
    for (auto& n : nums) {
        cout << n << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    auto result = findDisappearedNumbers(nums);
    print(result);
    nums = {1,1};
    result = findDisappearedNumbers(nums);
    print(result);
}