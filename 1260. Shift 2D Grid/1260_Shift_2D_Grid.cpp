#include <vector>
#include <iostream>
using namespace std;
//! @return the matrix after shifting the elements k steps to the right.
//! @param grid a matrix of integers
//! @author Nhut Nguyen
vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
    vector<int> v;
    for (auto& r : grid) {
        v.insert(v.end(), r.begin(), r.end());
    }
    const int m = grid.size();
    const int n = grid[0].size();
    int p = v.size() - (k % v.size());
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (p == v.size()) {
                p = 0;
            }
            grid[i][j] = v[p++];
        }
    }
    return grid;
}
void printResult(vector<vector<int>>& grid) {
    cout << "[";
    for (auto& r : grid) {
        cout << "[";
        for (int a: r) {
            cout << a << ",";
        }
        cout << "]";
    }
    cout << "]\n";
}
int main() {
    vector<vector<int>> grid{{1,2,3},{4,5,6},{7,8,9}};
    auto result = shiftGrid(grid, 1);
    printResult(result);
    grid = {{3,8,1,9},{19,7,2,5},{4,6,11,10},{12,0,21,13}};
    result = shiftGrid(grid, 4);
    printResult(result);
    grid = {{1,2,3},{4,5,6},{7,8,9}};
    result = shiftGrid(grid, 9);
    printResult(result);
}