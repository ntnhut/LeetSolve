#include <vector>
#include <iostream>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {        
    vector<bool> exist(nums.size() + 1, false);        
    for (auto& i : nums) {
        exist[i] = true;
    }
    vector<int> result;
    for (int i = 1; i <= nums.size(); i++) {
        if (!exist[i]) {
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