#include <iostream>
#include <unordered_map>
using namespace std;

//! @return true if t is an anagram of s, 
//!         i.e. each of its letters was reordered.
//! @author Nhut Nguyen
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    unordered_map<char, int> alphabet;
    for (char& c : s) {
        alphabet[c]++;
    }
    for (char& c : t) {
        alphabet[c]--;
        if (alphabet[c] < 0) {
            return false;
        }
    }
    return true;    
}

int main() {
    cout << isAnagram("anagæam", "nagaæam") << endl;
    cout << isAnagram("rat", "car") << endl;
}