
#include <vector>
#include <iostream>
using namespace std;

//! @param nums a vector containing n + 1 integers.
//! @cond 1 <= nums[i] <= n. 
//! @cond all the integers in nums appear only once
//!       except one appears two or more times.
//! @return the repeated number in nums
//! @author Nhut Nguyen
int findDuplicate(vector<int>& nums) {
    vector<bool> visited(nums.size());
    for (int a : nums) {
        if (visited[a]) {
            return a;
        }
        visited[a] = true;
    }
    return 0;
}

int main() {
    vector<int> nums{1,3,4,2,2};
    cout << findDuplicate(nums) << endl;    // 2
    nums = {3,1,3,4,2};
    cout << findDuplicate(nums) << endl;    // 3
}

// #include <bitset>
// int findDuplicate(vector<int>& nums) {
//     // Constraint: n <= 10^5
//     bitset<100001> visited;
//     for (int a : nums) {
//         if (visited[a]) {
//             return a;
//         }
//         visited[a] = 1;
//     }
//     return 0;
// }
