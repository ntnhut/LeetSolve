#include <iostream>
using namespace std;

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    int alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = 0;
    }
    for (char& c : s) {
        alphabet[c - 'a']++;
    }
    for (char& c : t) {
        alphabet[c - 'a']--;
        if (alphabet[c - 'a'] < 0) {
            return false;
        }
    }
    return true;    
}

int main() {
    cout << isAnagram("anagram", "nagaram") << endl;
    cout << isAnagram("rat", "car") << endl;
}