#include <vector>
#include <cassert>
// int maxProfit1(std::vector<int>& prices) {
//     int totalProfit = 0;
//     for (unsigned short i = 1; i < prices.size(); ++i) {
//         // Greedy approach: Just buy and sell on every upward slope
//         if (prices[i] > prices[i - 1]) {
//             totalProfit += prices[i] - prices[i - 1];
//         }
//     }
//     return totalProfit;
// }
int maxProfit(std::vector<int>& prices) {
    int totalProfit = 0;
    for (unsigned short i = 1; i < prices.size(); ++i) {
        int profit = prices[i] - prices[i - 1];
        totalProfit += std::max(profit, 0);
    }
    return totalProfit;
}


int main() {
    std::vector<int> prices = {7,1,5,3,6,4};
    assert(maxProfit(prices) == 7);
    prices = {1,2,3,4,5};
    assert(maxProfit(prices) == 4);
    prices = {7,6,4,3,1};
    assert(maxProfit(prices) == 0);
    return 0;
}