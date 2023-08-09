
#include <iostream>
using namespace std;
//! @param n a positive integer
//! @return return the number of strings of length n 
//!         that consist only of vowels (a, e, i, o, u)
//!          and are lexicographically sorted.
//! @author Nhut Nguyen
int countVowelStrings(int n) {    
    return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
}
int main() {
    cout << countVowelStrings(1) << endl;
    cout << countVowelStrings(2) << endl;
    cout << countVowelStrings(33) << endl;
}

