#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//! @return the largest subset whose any element divides some other element.
//! @param nums an array of positive integers
//! @author Nhut Nguyen
vector<int> largestDivisibleSubset(vector<int>& nums) {
    if (nums.size() <= 1) {
        return nums; 
    }
    sort(nums.begin(), nums.end());
    int maxSize = 0;    // the size of the resulting subset
    int maxindex = 0;   // nums[maxindex] is the largest value of the resulting subset
    vector<int> subsetSize(nums.size(), 1); // subsetSize[i] stores the size of the
                                            //  largest subset having biggest number nums[i]
    vector<int> pre(nums.size(), -1);       // pre[i] stores the previous index of 
                                            //  i in their largest subset
    for (int i = 0; i < nums.size(); i++) {
        // find the previous nums[j] that make subsetSize[i] largest
        for (int j = i - 1; j >= 0; j--) {

            if (nums[i] % nums[j] == 0 && subsetSize[j] + 1 > subsetSize[i]) {
                subsetSize[i] = subsetSize[j] + 1;
                pre[i] = j;
            }
        }
        // update the largest subset
        if (maxSize < subsetSize[i]) {
            maxSize = subsetSize[i];
            maxindex = i;
        }
    }
    vector<int> result;
    while (maxindex != -1) {
        result.push_back(nums[maxindex]);
        maxindex = pre[maxindex];
    }
    return result;        
}
void printSolution(vector<int>& result) {
    cout << "[";
    for (auto& v : result) {
        cout << v << ",";
    }
    cout << "]" << endl;
}
int main() {
    vector<int> nums{2,1,3};
    auto result = largestDivisibleSubset(nums);
    printSolution(result);
    nums = {1,2,4,8};
    result = largestDivisibleSubset(nums);
    printSolution(result);
}