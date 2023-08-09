#include <iostream>
using namespace std;
//! @return true if n is a power of three
//! @param n a 32-bit integer
//! @author Nhut Nguyen
bool isPowerOfThree(int n) {
    return n > 0 && 1162261467 % n == 0;
}
int main() {
    cout << isPowerOfThree(27) << endl;
    cout << isPowerOfThree(0) << endl;
    cout << isPowerOfThree(-1) << endl;
}