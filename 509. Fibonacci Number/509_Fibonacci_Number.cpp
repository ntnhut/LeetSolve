#include <iostream>
#include <vector>

//! @return the n-th number of the Fibonacci sequence
//! @author Nhut Nguyen
int fib(int n) {
    if (n <= 1) {
        return n;
    }
    int f0 = 0;
    int f1 = 1;
    for (int i = 2; i <= n; i++) {
        int f2 = f1 + f0;
        f0 = f1;
        f1 = f2;
    }
    return f1;
}


int main() {
    std::cout << fib(2) << std::endl;
    std::cout << fib(3) << std::endl;
    std::cout << fib(4) << std::endl;
}