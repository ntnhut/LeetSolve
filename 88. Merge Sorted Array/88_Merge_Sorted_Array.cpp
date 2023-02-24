#include <iostream>
#include <vector>
using namespace std;

//! @brief merge them into a sorted nums1.
//! @param nums1, m, nums2, n two sorted vectors of integers and their length
//! @author Nhut Nguyen
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {    
    int k = m + n - 1;
    int i = m - 1;
    int j = n - 1;
    while (k >= 0) {
        if (j < 0) {
            nums1[k--] = nums1[i--];
        } else if (i < 0) {
            nums1[k--] = nums2[j--];
        } else {
            nums1[k--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--]; 
        }
    }
}

void printResult(vector<int>& nums1) {
    cout << "[";
    for (int n : nums1) {
        cout << n << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    merge(nums1, 3, nums2, 3);
    printResult(nums1);
    nums1 = {1};
    nums2 = {};
    merge(nums1, 1, nums2, 0);
    printResult(nums1);
    nums1 = {0};
    nums2 = {1};
    merge(nums1, 0, nums2, 1);
    printResult(nums1);
}