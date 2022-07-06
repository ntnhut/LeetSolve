#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

int maxOperations(vector<int>& nums, int k) {
    unordered_map<int,int> m;
    int count = 0;
    for (int a : nums) {
        m[a]++;
        if (m[k - a] > 0) {
            if (a != k - a || m[a] >= 2) {
                count++;
                m[a]--;
                m[k - a]--;
            }
        }
    }
    return count;
}

int main() {
    vector<int> nums{1,2,3,4};
    cout << maxOperations(nums, 5) << endl;
    nums = {3,1,3,4,3};
    cout << maxOperations(nums, 6) << endl;
}