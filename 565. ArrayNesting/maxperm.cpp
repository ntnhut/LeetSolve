#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int arrayNesting(vector<int>& nums) {
    int maxLen(0);
    vector<bool> visited(nums.size());
    for (auto i : nums) {
        if (visited[i]) {
            continue;
        }
        int len(0);
        while (!visited[i]) {
            visited[i] = true;
            i = nums[i];            
            len++;
        }
        maxLen = max(len, maxLen);
    }
    return maxLen;
}

int main() {
    vector<int> nums = {5,4,0,3,1,6,2}; 
    cout << arrayNesting(nums) << endl; //4
    nums = {0,1,2}; 
    cout << arrayNesting(nums) << endl; // 1
    nums = {0,2,1}; 
    cout << arrayNesting(nums) << endl; // 2
    nums = {2,0,1}; 
    cout << arrayNesting(nums) << endl; // 3
}