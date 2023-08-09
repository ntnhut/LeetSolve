#include <vector>
#include <iostream>
using namespace std;
enum Direction {RIGHT, DOWN, LEFT, UP};
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> m(n, vector<int>(n));
    int bottom = n - 1;
    int right = n - 1;
    int top = 0;
    int left = 0;
    int row = 0;
    int col = 0;
    Direction d = RIGHT;
    int a = 1;
    while (top <= bottom && left <= right) {
        m[row][col] = a++;
        switch (d) {
            case RIGHT:
                if (col == right) {
                    top++;
                    d = DOWN;
                    row++;
                } else {
                    col++;
                }
                break;
            case DOWN:
                if (row == bottom) {
                    right--;
                    d = LEFT;
                    col--;
                } else {
                    row++;
                }
                break;
            case LEFT:
                if (col == left) {
                    bottom--;
                    d = UP;
                    row--;
                } else {
                    col--;
                }
                break;
            case UP:
                if (row == top) {
                    left++;
                    d = RIGHT;
                    col++;
                } else {
                    row--;
                }
                break;
        }
    }
    return m;
}
void printResult(vector<vector<int>>& m) {
    cout << "[";
    for (auto& r : m) {
        cout << "[";
        for (int a : r) {
            cout << a << ",";
        }
        cout << "]";
    }
    cout << "]\n";
}
int main() {
    auto m = generateMatrix(3);
    printResult(m);
    m = generateMatrix(1);
    printResult(m);
}