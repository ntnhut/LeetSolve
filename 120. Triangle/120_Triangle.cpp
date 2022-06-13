#include <iostream>

#include <vector>
#include <algorithm>
using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    vector<int> minTotal(triangle.size());
    minTotal[0] = triangle[0][0];
    for (int i = 1; i < triangle.size(); i++) {
        minTotal[i] = triangle[i][i] + minTotal[i - 1];
        for (int j = i - 1; j > 0; j--) {
            minTotal[j] = triangle[i][j] + min(minTotal[j - 1], minTotal[j]);
        }
        minTotal[0] = triangle[i][0] + minTotal[0];
    }
    return *min_element(minTotal.begin(), minTotal.end());
}

int main() {
    vector<vector<int>> triangle{{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << minimumTotal(triangle) << endl;
    triangle = {{-10}};
    cout << minimumTotal(triangle) << endl;
}