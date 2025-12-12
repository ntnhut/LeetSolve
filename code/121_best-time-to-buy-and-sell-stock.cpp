#include <vector>
#include <algorithm>
#include <cassert>
// int maxProfit1(std::vector<int>& prices) {
//     // Invariant: max_profit is the max profit so far
//     int max_profit = 0;
//     // Invariant: max_price is the max price from the current position to the end
//     int max_price = prices[prices.size() - 1];

//     for (int i = prices.size() - 2; i >= 0; i--)
//     {
//         // Update invariants max_profit and max_price
//         max_profit = std::max(max_price - prices[i], max_profit);
//         max_price = std::max(prices[i], max_price);
//     }
//     return max_profit;
// }
int maxProfit(std::vector<int>& prices) {
    if (prices.empty()) return 0;
    int min_price = prices[0];
    int max_profit = 0;

    for (int i = 1; i < prices.size(); ++i) {
        // Update min_price if the current price is lower
        min_price = std::min(min_price, prices[i]);
        // Calculate potential profit and update max_profit if it's higher
        max_profit = std::max(max_profit, prices[i] - min_price);
    }
    return max_profit;
}

int main() {
    std::vector<int> prices = {7,1,5,3,6,4};
    assert(maxProfit(prices) == 5);
    prices = {1,2,3,4,5};
    assert(maxProfit(prices) == 4);
    prices = {7,6,4,3,1};
    assert(maxProfit(prices) == 0);
    return 0;
}