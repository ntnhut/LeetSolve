#include <vector>
#include <iostream>
using namespace std;

//! @param prices a vector of a stock's prices in time.
//! @return the maximum profit you can achieve by choosing
//!         one day to buy and another day to sell.
//! @author Nhut Nguyen
int maxProfit(vector<int>& prices) {
    int maxProfit = 0;
    int minPrice = prices[0];
    for (int i = 1; i < prices.size(); i++)  {
        minPrice = min(minPrice, prices[i]);
        maxProfit = max(maxProfit, prices[i] - minPrice);
    }
    return maxProfit;
}

int main() {
    vector<int> prices{7,1,5,3,6,4};
    cout << maxProfit(prices) << endl; // 5
    prices = {7,6,4,3,1};
    cout << maxProfit(prices) << endl; // 0
    prices = {2,4,1,7};
    cout << maxProfit(prices) << endl; // 6
    prices = {2,4,1};
    cout << maxProfit(prices) << endl; // 2
}