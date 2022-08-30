#include <iostream>
#include <vector>
using namespace std;
void rotate(vector<vector<int>>& matrix) {
    const int n = matrix.size();
    // transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    // vertical mirror
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++ ) {
            swap(matrix[i][j], matrix[i][n - 1 - j]);
        }
    }
}
void printMatrix(vector<vector<int>>& matrix) {
    cout << "[";
    for (auto& row: matrix) {
        cout << "[";
        for (auto& a: row) {
            cout << a << ",";
        }
        cout << "],";
    }
    cout << "]\n";
}
int main() {
    vector<vector<int>> matrix{{1,2,3},{4,5,6},{7,8,9}};
    rotate(matrix);
    printMatrix(matrix);
    matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    rotate(matrix);
    printMatrix(matrix);
}