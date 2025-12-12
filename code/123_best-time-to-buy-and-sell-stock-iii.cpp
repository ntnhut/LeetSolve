#include <vector>
#include <algorithm>
#include <cassert>
int maxProfitSingleTransaction(const std::vector<int>& prices, int start, int end) {
    int min_price = prices[start];
    int max_profit = 0;
    for (int i = start + 1; i <= end; ++i) {
        max_profit = std::max(max_profit, prices[i] - min_price);
        min_price = std::min(min_price, prices[i]);
    }
    return max_profit;
}
// int maxProfit1(std::vector<int>& prices) {
//     int n = prices.size();
//     if (n == 0) return 0;

//     int max_total_profit = 0;

//     // Try splitting the array into two parts at every possible index
//     for (int i = 0; i < n; ++i) {
//         int profit1 = maxProfitSingleTransaction(prices, 0, i);
//         int profit2 = maxProfitSingleTransaction(prices, i + 1, n - 1);
//         max_total_profit = std::max(max_total_profit, profit1 + profit2);
//     }

//     return max_total_profit;
// }
// int maxProfit2(std::vector<int>& prices) {
//     int n = prices.size();
//     if (n == 0) return 0;

//     std::vector<int> left_profits(n, 0);
//     std::vector<int> right_profits(n, 0);

//     // Calculate max profit for one transaction from the left
//     int min_price = prices[0];
//     for (int i = 1; i < n; ++i) {
//         min_price = std::min(min_price, prices[i]);
//         left_profits[i] = std::max(left_profits[i - 1], prices[i] - min_price);
//     }

//     // Calculate max profit for one transaction from the right
//     int max_price = prices[n - 1];
//     for (int i = n - 2; i >= 0; --i) {
//         max_price = std::max(max_price, prices[i]);
//         right_profits[i] = std::max(right_profits[i + 1], max_price - prices[i]);
//     }

//     // Combine the two profits
//     int max_total_profit = 0;
//     for (int i = 0; i < n; ++i) {
//         max_total_profit = std::max(max_total_profit, left_profits[i] + right_profits[i]);
//     }

//     return max_total_profit;
// }

// int maxProfit3(std::vector<int>& prices) {
//     // compute only left profits, 
//     // then compute right profits on the fly and combine
//     int n = prices.size();
//     if (n == 0) return 0;
//     std::vector<int> left_profits(n, 0);
//     int optimal_price = prices[0];
//     for (int i = 1; i < n; ++i) {
//         optimal_price = std::min(optimal_price, prices[i]);
//         left_profits[i] = std::max(left_profits[i - 1], prices[i] - optimal_price);
//     }
//     int max_total_profit = 0;
//     optimal_price = prices[n - 1];
//     for (int i = n - 2; i >= 0; --i) {
//         optimal_price = std::max(optimal_price, prices[i]);
//         max_total_profit = std::max(max_total_profit, left_profits[i] + optimal_price - prices[i]);
//     }
//     return max_total_profit;
// }
int maxProfit(std::vector<int>& prices) {
    // Initialize buy states to very small number (infinity)
    // because we want to maximize the negative cost.
    int buy1_balance = -10001;
    int sell1_balance = 0;
    int buy2_balance = -10001;
    int sell2_balance = 0;

    for (int price : prices) {
        // 1. Maximize balance after 1st Buy (Minimize 1st cost)
        buy1_balance = std::max(buy1_balance, -price);

        // 2. Maximize balance after 1st Sell
        sell1_balance = std::max(sell1_balance, buy1_balance + price);

        // 3. Maximize balance after 2nd Buy (Reinvesting profit from sell1)
        buy2_balance = std::max(buy2_balance, sell1_balance - price);

        // 4. Maximize balance after 2nd Sell
        sell2_balance = std::max(sell2_balance, buy2_balance + price);
    }

    return sell2_balance;
}
int main() {
    std::vector<int> prices = {3,3,5,0,0,3,1,4};
    assert(maxProfit(prices) == 6);
    prices = {1,2,3,4,5};
    assert(maxProfit(prices) == 4);
    prices = {7,6,4,3,1};
    assert(maxProfit(prices) == 0);
    return 0;
}