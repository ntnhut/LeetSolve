#include <iostream>
using namespace std;


//! @param n a string of decimal integer
//! @return the minimum number of positive deci-binary numbers
//!         needed so that they sum up to n.
//! @author Nhut Nguyen
int minPartitions(string n) {
    char maxDigit = '0';
    for (char& d : n) {
        maxDigit = max(maxDigit, d);
    }
    return maxDigit - '0';
}


int main() {
    cout << minPartitions("32") << endl;
    cout << minPartitions("82734") << endl;
    cout << minPartitions("27346209830709182346") << endl;
}