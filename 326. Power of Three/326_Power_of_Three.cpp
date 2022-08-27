#include <iostream>
using namespace std;
bool isPowerOfThree(int n) {
    while (n % 3 == 0 && n > 0) {
        n /= 3;
    }
    return n == 1;

}
int main() {
    cout << isPowerOfThree(27) << endl;
    cout << isPowerOfThree(0) << endl;
    cout << isPowerOfThree(9) << endl;
}