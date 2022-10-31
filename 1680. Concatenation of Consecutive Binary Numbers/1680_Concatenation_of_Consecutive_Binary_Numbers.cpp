#include <cmath>
#include <iostream>

//! @param n a positive integer
//! @return the decimal value of the binary string formed by concatenating
//!         the binary representations of 1 to n in order, modulo 10^9 + 7.
//! @example For n = 3, return 27.
//!         Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
//!         After concatenating them, we have "11011", 
//!         which corresponds to the decimal value 27.
//! @author Nhut Nguyen
int concatenatedBinary(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        const int num_bits = std::log2(i) + 1;        
        result = ((result << num_bits) + i) % 1000000007;
    }
    return result;
}
int main() {
    std::cout << concatenatedBinary(1) << std::endl;
    std::cout << concatenatedBinary(3) << std::endl;
    std::cout << concatenatedBinary(12) << std::endl;
}