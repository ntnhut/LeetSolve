#include <vector>
#include <iostream>
#include <string>
#include <numeric>
using namespace std;

//! @param ops a vector of strings, each is either "C", "D", "+"
//!            or a signed integer.
//! @return the sum of all records after all operations. 
//! @author Nhut Nguyen
int calPoints(vector<string>& ops) {
    vector<int> stk;
    for (string& s : ops) {
        if (s == "C") {
            stk.pop_back();
        } else if (s == "D") {
            stk.push_back(stk.back() * 2);
        } else if (s == "+") {
            stk.push_back(stk[stk.size() - 1] + stk[stk.size() - 2]);
        } else {
            stk.push_back(stoi(s));
        }
    }
    return accumulate(stk.begin(), stk.end(), 0);
}

int main() {
    vector<string> ops{"5","2","C","D","+"};
    cout << calPoints(ops) << endl;
    ops = {"5","-2","4","C","D","9","+","+"};
    cout << calPoints(ops) << endl;
}