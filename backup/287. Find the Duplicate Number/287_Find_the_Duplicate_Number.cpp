#include <vector>
#include <iostream>
#include <bitset>
using namespace std;

//! @return the repeated number in nums
//! @param nums a vector containing n + 1 integers from 1 to n
//! @author Nhut Nguyen
int findDuplicate(vector<int>& nums) {
    // Constraint: n <= 10^5
    bitset<100001> visited;
    for (int a : nums) {
        if (visited[a]) {
            return a;
        }
        visited[a] = 1;
    }
    return 0;
}
int main() {
    vector<int> nums{1,3,4,2,2};
    cout << findDuplicate(nums) << endl;
    nums = {3,1,3,4,2};
    cout << findDuplicate(nums) << endl;
}