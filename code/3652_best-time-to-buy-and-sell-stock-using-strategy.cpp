#include <vector>
#include <cassert>
#include <iostream>
#include <numeric>
using namespace std;
long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {

    const int N = prices.size();
    vector<long long> sum(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        sum[i] = sum[i - 1] + prices[i - 1] * strategy[i - 1];
    }
    long long max_profit = sum[N];
    const int end = N - k;
    const int half_k = k / 2;
    long long half_k_prices = accumulate(prices.begin() + half_k - 1, prices.begin() + k - 1, 0LL);
    for (int i = 0; i <= end; ++i) {
        half_k_prices = half_k_prices - prices[i + half_k - 1] + prices[i + k - 1];
        max_profit = max(max_profit, sum[i] + half_k_prices + sum[N] - sum[i + k]);
    }
    return max_profit;
}
int main() {
    {
        vector<int> prices = {4,2,8};
        vector<int> strategy = {-1,0,1};
        auto result = maxProfit(prices, strategy, 2);
        cout << result << endl;
        assert(result == 10);
    }
    {
        vector<int> prices = {5,4,3};
        vector<int> strategy = {1,1,0};
        auto result = maxProfit(prices, strategy, 2);
        cout << result << endl;
        assert(result == 9);
    }
    {
        vector<int> prices = {5,8};
        vector<int> strategy = {-1,-1};
        auto result = maxProfit(prices, strategy, 2);
        cout << result << endl;
        assert(result == 8);
    }
    return 0;
}
