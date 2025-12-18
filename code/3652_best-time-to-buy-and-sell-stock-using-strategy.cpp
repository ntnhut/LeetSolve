#include <vector>
#include <cassert>
#include <iostream>
#include <numeric>
using namespace std;
long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {

    const int N = prices.size();
    long long remaining_profit = 0;
    long long half_k_profit = 0;
    const int half_k = k / 2;
    long long first_k_profit = 0;
    for (int i = 0; i < N; ++i) {
        auto v = prices[i] * strategy[i];
        if (i < k) {
            first_k_profit += v;
            if (i >= half_k) {
                half_k_profit += prices[i];
            }
        }
        else {
            remaining_profit += v;
        }
    }
    long long max_profit = max(first_k_profit, half_k_profit) + remaining_profit;
   
    for (int i = k; i < N; ++i) {
        half_k_profit += prices[i] - prices[i - half_k];
        remaining_profit += prices[i - k] * strategy[i - k] - prices[i] * strategy[i];
        max_profit = max(max_profit, remaining_profit + half_k_profit);
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
