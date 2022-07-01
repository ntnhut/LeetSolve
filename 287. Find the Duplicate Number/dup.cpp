#include <vector>
#include <iostream>
#include <bitset>
using namespace std;

int findDuplicate(vector<int>& nums) {
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