
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
//! @param words an array of strings of lowercase English letters
//! @return the number of unique Morse representations encoded by the words
//! @author Nhut Nguyen
int uniqueMorseRepresentations(vector<string>& words) {
    vector<string> morse{".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                        "....", "..", ".---", "-.-", ".-..", "--", "-.",
                        "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                        "...-", ".--", "-..-", "-.--", "--.."};
    unordered_set<string> transformations;
    for (string& w : words) {
        string s{""};
        for (char& c : w) {
            s += morse[c - 'a'];
        }
        transformations.insert(s);
    }
    return transformations.size();
}
int main() {
    vector<string> words{"gin","zen","gig","msg"};
    cout << uniqueMorseRepresentations(words) << endl;
    words = {"a"};
    cout << uniqueMorseRepresentations(words) << endl;
}
// Output:
// 2 ("--...-." and "--...--.")
// 1

