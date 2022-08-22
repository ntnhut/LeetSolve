#include <iostream>
using namespace std;

//! @param n an integer.
//! @return true if n is a power of four,
//!         false otherwise.
//! @author Nhut Nguyen
bool isPowerOfFour(int n) {
    return n > 0 
        && (n & (n - 1)) == 0 
        && (n & 0x55555555) != 0;
}

int main() {
    cout << isPowerOfFour(16) << endl;
    cout << isPowerOfFour(5) << endl;
    cout << isPowerOfFour(1) << endl;
}