#include <iostream>
#include <vector>
using namespace std;
//! @brief Repeatedly remove k adjacent letters on s until you no longer can. 
//! @return the final string
//! @param s a string of lower case English letters
//! @author Nhut Nguyen
string removeDuplicates(string s, int k) {
    vector<string> stk;
    int i = 0;
    while (i < s.length()) {
        string a;
        if (!stk.empty() && s[i] == stk.back().back()) {
            a = move(stk.back());
            stk.pop_back();
        }
        int j = i;
        while (j < s.length() && s[j] == s[i]) {
            a += s[j];
            j++;
            if (a.length() == k) {
                a = "";
            }
        }
        if (!a.empty()) {
            stk.push_back(a);
        }
        i = j;
    }
    s = "";
    for (auto& str : stk) {
        s += str;
    }
    return s;
}
int main() {
    cout << removeDuplicates("abcd", 2) << endl;
    cout << removeDuplicates("deeedbbcccbdaa", 3) << endl;
    cout << removeDuplicates("pbbcggttciiippooaais", 2) << endl;
}