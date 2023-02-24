#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

//! @return true if you can construct the target from a vector arr of n numbers 1
//!         by repeatedly replacing any element with the sum of arr. 
//! @param target a vector of n positive integers.
//! @author Nhut Nguyen
bool isPossible(vector<int>& target) {
    priority_queue<int> q(target.begin(), target.end());
    unsigned long sum = accumulate(target.begin(), target.end(), (unsigned long) 0);
    while (q.top() > 1) {
        sum -= q.top();
        if (sum == 1) {
            return true;
        }
        if (q.top() <= sum) {
            return false;
        }
        if (sum == 0) {
            return false;
        }
        int pre = q.top() % sum;
        if (pre == 0) {
            return false;
        }
        q.pop();
        q.push(pre);
        sum += pre;
    }
    return sum == target.size();
}

int main() {
    vector<int> target{9,3,5};
    cout << isPossible(target) << endl;
    target = {1,1,1,2};
    cout << isPossible(target) << endl;
    target = {8,5};
    cout << isPossible(target) << endl;
}