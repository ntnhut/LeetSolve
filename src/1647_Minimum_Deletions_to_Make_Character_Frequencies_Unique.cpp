#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//! @return the minimum number of characters you need to delete 
//!         to make the string s have no two different characters
//!         that have the same frequency.
//! @author Nhut Nguyen
int minDeletions(string s) {
    vector<int> freq(26, 0);
    for (char& c: s) {
        freq[c - 'a']++;
    }
    sort(freq.begin(), freq.end(), greater<int>());
    int deletion = 0;
    int currentFreq = freq[0];
    for (int i = 1; i < freq.size() && freq[i] > 0; i++) {
        if (currentFreq == 0) {
            deletion += freq[i];
        } else if (freq[i] >= currentFreq) {
            deletion += freq[i] - currentFreq + 1;
            currentFreq--;
        } else {
            currentFreq = freq[i];
        }
    }
    return deletion;
}

int main() {
    cout << minDeletions("aab") << endl;
    cout << minDeletions("aaabbbcc") << endl;
    cout << minDeletions("ceabaacb") << endl;
}