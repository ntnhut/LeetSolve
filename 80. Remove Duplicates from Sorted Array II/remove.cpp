#include <vector>
#include <iostream>
using namespace std;
//! @param nums a sorted vector of integers
//! @return the number of remain elements after removing duplicates
//!         such that each unique element appears at most twice.
//! @author Nhut Nguyen
int removeDuplicates(vector<int>& nums) {
    if (nums.size() <= 2) {
        return nums.size(); 
    } 
    int k = 2; 
    int i = 2;
    while (i < nums.size()) {
        if (nums[i] > nums[k - 2]) {
            nums[k++] = nums[i];
        }
        i++;
    }
    return k;
}
void printResult(const int k, const vector<int>& nums) {
    cout << k << ", [";
    for (int i = 0; i < k ; i++) {
        cout << nums[i] << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums{1,1,1,2,2,3};
    printResult(removeDuplicates(nums), nums);
    nums = {0,0,1,1,1,1,2,3,3};
    printResult(removeDuplicates(nums), nums);
}