
#include <iostream>
using namespace std;

//! @param n an integer.
//! @return true if n is a power of four,
//!         false otherwise.
//! @author Nhut Nguyen
bool isPowerOfFour(int n) {
    while (n % 4 == 0 && n > 0) {
        n /= 4;
    }
    return n == 1;
}

int main() {
    cout << isPowerOfFour(16) << endl;  // 1
    cout << isPowerOfFour(5) << endl;   // 0
    cout << isPowerOfFour(1) << endl;   // 1
}

// bool isPowerOfFour(int n) {
//     return n > 0 
//         && (n & (n - 1)) == 0 
//         && (n & 0x55555555) != 0;
// }
