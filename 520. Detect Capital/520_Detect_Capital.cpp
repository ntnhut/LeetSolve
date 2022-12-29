#include <string>
#include <iostream>
using namespace std;

bool isValidCase(const char& c, const bool isLower) {
    if (isLower) {
        return 'a' <= c && c <= 'z';
    }
    return 'A' <= c && c <= 'Z';
}
//! @return true if if the usage of capitals in it is right
//! @param word a string
//! @author Nhut Nguyen
bool detectCapitalUse(string word) {
    if (word.length() == 1) {
        return true;
    }
    bool isLower = true;
    if (isValidCase(word[0], false) && isValidCase(word[1], false)) {
        isLower = false;
    }
    for (int i = 1; i < word.length(); i++) {
        if (!isValidCase(word[i], isLower)) {
            return false;
        }
    }
    return true;
}

int main() {
    cout << detectCapitalUse("USA") << endl;
    cout << detectCapitalUse("FlaG") << endl;
    cout << detectCapitalUse("leetcode") << endl;
    cout << detectCapitalUse("Google") << endl;
}