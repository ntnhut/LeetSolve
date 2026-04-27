#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <cassert>
using namespace std;
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        // [price, amount], who bought with higher prices will be executed first
        unordered_map<int, size_t> buyBacklog;
        priority_queue<int> buyPrices; // max heap for buy prices
        // who sold with lower prices will be executed first
        unordered_map<int, size_t> sellBacklog;
        priority_queue<int, vector<int>, greater<int>> sellPrices; // min heap for sell prices        
        size_t totalAmount = 0;
        
        for (auto& order : orders) { // can't use [price, amount, type]
            const int price = order[0];
            size_t amount = order[1];
            const int type = order[2];

            if (type == 0) { // buy
                while (!sellPrices.empty() && sellPrices.top() <= price && amount > 0) {
                    int sellPrice = sellPrices.top();
                    sellPrices.pop();
                    assert(sellBacklog[sellPrice] > 0);

                    size_t matched = min(amount, sellBacklog[sellPrice]);
                    amount -= matched;
                    sellBacklog[sellPrice] -= matched;
                    totalAmount -= matched;

                    if (sellBacklog[sellPrice] > 0) {
                        sellPrices.push(sellPrice);
                    }
                }
                if (amount > 0) { // add remaining to backlog
                    if (buyBacklog[price] == 0) { // new price level
                        buyPrices.push(price);
                    }
                    buyBacklog[price] += amount;
                    totalAmount += amount;                    
                }
 
            } else { // sell
                while (!buyPrices.empty() && buyPrices.top() >= price && amount > 0) {
                    int buyPrice = buyPrices.top();
                    buyPrices.pop();
                    assert(buyBacklog[buyPrice] > 0);

                    size_t matched = min(amount, buyBacklog[buyPrice]);
                    amount -= matched;
                    buyBacklog[buyPrice] -= matched;
                    totalAmount -= matched;
                    if (buyBacklog[buyPrice] > 0) {
                        buyPrices.push(buyPrice);
                    }
                }
                if (amount > 0) { // add remaining to backlog
                    if (sellBacklog[price] == 0) { // new price level
                        sellPrices.push(price);
                    }
                    sellBacklog[price] += amount;
                    totalAmount += amount;
                }
            }
        }

        return totalAmount % 1000000007;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> orders = {{10,5,0},{15,2,1},{25,1,1},{30,4,0}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 6
    orders = {{7,1000000000,1},{15,3,0},{5,999999995,0},{5,1,1}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 999999984
    // [[26,7,0],[16,1,1],[14,20,0],[23,15,1],[24,26,0],[19,4,1],[1,1,0]]
    orders = {{26,7,0},{16,1,1},{14,20,0},{23,15,1},{24,26,0},{19,4,1},{1,1,0}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 34
}