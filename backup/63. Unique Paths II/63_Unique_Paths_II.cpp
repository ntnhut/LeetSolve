#include <vector>
#include <iostream>
using namespace std;
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    const int row = obstacleGrid.size();
    const int col = obstacleGrid[0].size();
    vector<vector<int>> np(row, vector<int>(col, 0));    
    for (int i = 0; i < row && obstacleGrid[i][0] == 0; i++) {
        np[i][0] = 1;
    }    
    for (int j = 0; j < col && obstacleGrid[0][j] == 0; j++) {
        np[0][j] = 1;
    }
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (obstacleGrid[i][j] == 0) {
                np[i][j] += np[i - 1][j] + np[i][j - 1];
            }
        }
    }
    return np[row - 1][col - 1]; 
}
int main() {
    vector<vector<int>> obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}};
    cout << uniquePathsWithObstacles(obstacleGrid) << endl;
    obstacleGrid = {{0,1},{0,0}};
    cout << uniquePathsWithObstacles(obstacleGrid) << endl;
}