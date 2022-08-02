#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countLessOrEqual(const vector<vector<int>>& matrix, int x) {
    int count = 0;
    for (const auto& row : matrix) {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }
    return count;
}
int kthSmallest(vector<vector<int>>& matrix, int k) {   
    int left = matrix.front().front();
    int right = matrix.back().back();
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (countLessOrEqual(matrix, mid) >= k) {
            right = mid - 1;
        } else {
            left = mid + 1; 
        }
    }
    return left;
}

int main() {
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    cout << kthSmallest(matrix, 8) << endl;
    matrix = {{-5}};
    cout << kthSmallest(matrix, 1) << endl;
}