#include <vector>
#include <iostream>
#include <queue>
using namespace std;

//! @brief  smash two heaviest stones x <= y each time. 
//!         If x == y, both are destroyed. 
//!         Otherwise, a new stone of weight y - x is created.
//! @return the smallest possible weight of the left stone. 
//!         If there are no stones left, return 0.
//! @param stones an array of stone weights
//! @author Nhut Nguyen
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> q(stones.begin(), stones.end());
    while (q.size() >= 2) {
        int y = q.top();
        q.pop();
        int x = q.top();
        q.pop();
        if (y != x) {
            q.push(y - x);
        }
    }
    return q.empty() ? 0 : q.top();    
}

int main() {
    vector<int> stones{2,7,4,1,8,1};
    cout << lastStoneWeight(stones) << endl;
    stones = {1};
    cout << lastStoneWeight(stones) << endl;
}