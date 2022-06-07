#include <iostream>

//! @return the number of positions at which the corresponding bits
//!         are different between x and y
//! @author Nhut Nguyen
int hammingDistance(int x, int y) {
    int z = x ^ y;
    int count = 0;
    while (z) {
        count += z & 1;
        z = z >> 1;
    }
    return count;
}

int main() {
    std::cout << hammingDistance(1,4) << std::endl; // 2
    std::cout << hammingDistance(1,3) << std::endl; // 1
}