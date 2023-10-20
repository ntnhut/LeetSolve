#include<vector>
#include<iostream>
#include <algorithm>
#include<unordered_map>
using namespace std;
//! @param nums an array of integers, half of them are odd, and the other half are even.
//! @return the sorted array so that nums[i] has the same parity with i
//! @author Nhut Nguyen
vector<int> sortArrayByParityII(vector<int>& nums) {
    int N = nums.size();
    int evenPos = 0;
    int oddPos = N - 1;
    while (evenPos < N) {
        // find the nums[evenPos] that is odd for swapping
        while (evenPos < N && nums[evenPos] % 2 == 0) {
            evenPos += 2;
        }
        // If not found, it means all even nums are in place. Done! 
        if (evenPos >= N) {
            break;
        }
        // Otherwise, the problem's constraint makes sure 
        // there must be some nums[oddPos] that is even for swapping
        while (oddPos >= 0 && nums[oddPos] % 2 == 1) {
            oddPos -= 2;
        } 
        swap(nums[evenPos], nums[oddPos]);
    }
    return nums;
}
void print(vector<int>& nums) {
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;
}
int main() {
    vector<int> nums = {4,2,5,7};
    auto result = sortArrayByParityII(nums);
    print(result); // 4 5 2 7
    nums = {1,0,7,3,8,9,2,5,4,1,2,4};
    result = sortArrayByParityII(nums);
    print(result); // 4 7 0 3 8 9 2 5 4 1 2 1
    nums = {3,4};
    result = sortArrayByParityII(nums);
    print(result); // 4 3
    nums = {648,831,560,986,192,424,997,829,897,843};
    result = sortArrayByParityII(nums);
    print(result); // 648 831 560 897 192 997 424 829 986 843

}