#include <vector>
#include <iostream>
using namespace std;

//! @return an array answer such that answer[i] is equal to the product of
//!         all the elements of nums except nums[i].
//! @param nums an array of integers
//! @cond  You must write an algorithm that runs in O(n) time and 
//!        without using the division operation.
//! @author Nhut Nguyen
vector<int> productExceptSelf(vector<int>& nums) {
    const int n = nums.size();
    vector<int> answer(n);
    answer[0] = 1;
    for (int i = 1; i < n; i++) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }
    int after = 1;
    for (int i = n - 2; i >= 0; i--) {
        after *= nums[i + 1];
        answer[i] *= after;
    }
    return answer;
}

void print(vector<int>& nums) {
    for (auto& v : nums) {
        cout << v << " ";
    }
    cout << endl;
}
int main() {
    vector<int> nums = {1, 2, 3, 4};
    auto answer = productExceptSelf(nums);
    print(answer);
    nums = {-1, 1, 0, -3, 3};
    answer = productExceptSelf(nums);
    print(answer);
}