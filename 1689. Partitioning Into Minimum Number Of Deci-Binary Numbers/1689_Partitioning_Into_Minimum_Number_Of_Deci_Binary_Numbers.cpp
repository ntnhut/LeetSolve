#include <iostream>


using namespace std;
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