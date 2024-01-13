
#include <iostream>
#include <vector>
using namespace std;

//! @brief performs the backspace action on a given string s
//!         where '#' denotes the backspace action (back deletion)
//! @author Nhut Nguyen
string cleanString(string &s) {
    vector<char> v;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '#') {
            v.push_back(s[i]);
        } else {
            if (!v.empty()) {
                v.pop_back();
            }
        }
    }
    return string(v.begin(), v.end());
}

//! @return true if two strings s and t are equal 
//!         when both are typed into empty text editors
//!         and applying the backspace action.
bool backspaceCompare(string s, string t) {
    return cleanString(s) == cleanString(t);
}

int main() {
    cout << backspaceCompare("ab#c", "ad#c") << endl;   // 1
    cout << backspaceCompare("ab##", "c#d#") << endl;   // 1
    cout << backspaceCompare("a#c", "b") << endl;       // 0
}

