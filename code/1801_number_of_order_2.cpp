#include <vector>
#include <map>
#include <iostream>
using namespace std;
class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        // [price, amount], who bought with higher prices will be executed first
        map<int, size_t, std::greater<int>> buyBacklog;
        // who sold with lower prices will be executed first
        map<int, size_t> sellBacklog;
        size_t totalAmount = 0;

        
        for (auto& order : orders) { // can't use [price, amount, type]
            const int price = order[0];
            size_t amount = order[1];
            const int type = order[2];

            if (type == 0) { // buy
                auto it = sellBacklog.begin();
                while (it != sellBacklog.end() && it->first <= price && amount > 0) {

                    size_t matched = min(amount, it->second);
                    amount -= matched;
                    it->second -= matched;
                    totalAmount -= matched;
                    it = (it->second == 0) ? sellBacklog.erase(it) : next(it);
                }
                if (amount > 0) { // add remaining to backlog
                    buyBacklog[price] += amount;
                    totalAmount += amount;
                }
 
            } else { // sell
                auto it = buyBacklog.begin();
                while (it != buyBacklog.end() && it->first >= price && amount > 0) {
                    size_t matched = min(amount, it->second);
                    amount -= matched;
                    it->second -= matched;
                    totalAmount -= matched;
                    it = (it->second == 0) ? buyBacklog.erase(it) : next(it);
                }
                if (amount > 0) { // add remaining to backlog
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
    orders = {{26,7,0},{16,1,1},{14,20,0},{23,15,1},{24,26,0},{19,4,1},{1,1,0}};
    cout << sol.getNumberOfBacklogOrders(orders)<< endl; // 34
}