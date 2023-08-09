#include <iostream>
#include <vector>
using namespace std;
    int uniquePaths(int m, int n) {
        vector<int> dp(n,1);
        for (int i = 1; i <m; i++) {
            for (int j= 1; j<n;j++) {
                dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }
int main() {
    std::cout << uniquePaths(3,7) << std::endl; // 28
    std::cout << uniquePaths(7,3) << std::endl; // 28
    std::cout << uniquePaths(3,2) << std::endl; // 3
    std::cout << uniquePaths(3,3) << std::endl; // 6
}