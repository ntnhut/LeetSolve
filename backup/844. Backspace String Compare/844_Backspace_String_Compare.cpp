#include <iostream>
#include <vector>
using namespace std;

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
//! @return true if s and t are equal when both are typed into empty text editors.
//! @author Nhut Nguyen
bool backspaceCompare(string s, string t) {
    return cleanString(s) == cleanString(t);
}

int main() {
    cout << backspaceCompare("ab#c", "ad#c") << endl;
    cout << backspaceCompare("ab##", "c#d#") << endl;
    cout << backspaceCompare("a#c", "b") << endl;
}