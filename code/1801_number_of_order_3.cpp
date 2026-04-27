#include <vector>
#include <queue>
#include <iostream>
using namespace std;
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        const int mod = 1000000007;
        // [price, amount], highest buy price first
        priority_queue<pair<int, long long>> buyBacklog;
        // [price, amount], lowest sell price first
        priority_queue<pair<int, long long>, vector<pair<int, long long>>, greater<pair<int, long long>>> sellBacklog;

        for (const auto& order : orders) {
            int price = order[0];
            long long amount = order[1];
            int type = order[2];

            if (type == 0) { // buy
                while (!sellBacklog.empty() && sellBacklog.top().first <= price && amount > 0) {
                    auto [sellPrice, sellAmount] = sellBacklog.top();
                    sellBacklog.pop();

                    long long matched = min(amount, sellAmount);
                    amount -= matched;
                    sellAmount -= matched;

                    if (sellAmount > 0) {
                        sellBacklog.push({sellPrice, sellAmount});
                    }
                }

                if (amount > 0) {
                    buyBacklog.push({price, amount});
                }
            } else { // sell
                while (amount > 0 && !buyBacklog.empty() && buyBacklog.top().first >= price) {
                    auto [buyPrice, buyAmount] = buyBacklog.top();
                    buyBacklog.pop();

                    long long matched = min(amount, buyAmount);
                    amount -= matched;
                    buyAmount -= matched;

                    if (buyAmount > 0) {
                        buyBacklog.push({buyPrice, buyAmount});
                    }
                }

                if (amount > 0) {
                    sellBacklog.push({price, amount});
                }
            }
        }

        long long totalAmount = 0;
        while (!buyBacklog.empty()) {
            totalAmount = (totalAmount + buyBacklog.top().second) % mod;
            buyBacklog.pop();
        }
        while (!sellBacklog.empty()) {
            totalAmount = (totalAmount + sellBacklog.top().second) % mod;
            sellBacklog.pop();
        }

        return static_cast<int>(totalAmount);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> orders = {{10,5,0},{15,2,1},{25,1,1},{30,4,0}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 6
    orders = {{7,1000000000,1},{15,3,0},{5,999999995,0},{5,1,1}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 999999984
    orders = {{26,7,0},{16,1,1},{14,20,0},{23,15,1},{24,26,0},{19,4,1},{1,1,0}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 34
}