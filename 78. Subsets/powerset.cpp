#include <vector>
#include <iostream>
using namespace std;

//! @param nums An array of unique integers.
//! @return All possible subsets of nums (the powerset).
//! @author Nhut Nguyen
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> powerset = {{}};
    int i = 0;
    while (i < nums.size()) {
        vector<vector<int>> newSubsets;
        for (auto subset : powerset) {
            subset.push_back(nums[i]);  
            newSubsets.push_back(subset);
        }
        powerset.insert(powerset.end(), newSubsets.begin(), newSubsets.end());
        i++;
    }
    return powerset;
}

void print(vector<vector<int>>& powerset) {
    for (auto& set : powerset ) {
        cout << "[";
        for (auto& element : set) {
            cout << element << ",";
        }
        cout << "]";
    }
    cout << endl;
}
int main() {
    vector<int> nums{1,2,3};
    auto powerset = subsets(nums);
    print(powerset); 
    nums = {1};
    powerset = subsets(nums);
    print(powerset); 
}