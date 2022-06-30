#include <iostream>

using namespace std;
//! @param columnTitle A string representing the column title 
//!                    as appear in an Excel sheet
//! @return The corresponding column number.
//! @author Nhut Nguyen
int titleToNumber(string columnTitle) {
    int column = 0; 
    for (char c : columnTitle) {
        column = 26*column + (c - 64);
    }
    return column;
}

int main() {
    cout << titleToNumber("A") << endl; // 1
    cout << titleToNumber("AB") << endl; // 28
    cout << titleToNumber("ZY") << endl; // 701
}