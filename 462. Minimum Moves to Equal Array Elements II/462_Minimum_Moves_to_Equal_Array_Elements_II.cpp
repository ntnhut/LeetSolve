#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//! @return the minimum number of moves 
//!         required to make all array elements equal.
//! @note   In one move, you can increment or 
//!         decrement an element of the array by 1.
//! @param nums an array of integers
//! @author Nhut Nguyen
int minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    const int median = nums[nums.size() / 2];
    int moves = 0;
    for (int& a: nums) {
        moves += abs(a - median);
    }
    return moves;
}

int main() {
    vector<int> nums{1,2,3};
    cout << minMoves2(nums) << endl;
    nums = {1,10,2,9};
    cout << minMoves2(nums) << endl;
}