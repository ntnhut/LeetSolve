#include <iostream>
#include <unordered_map>
using namespace std;
int romanToInt(string s) {
    unordered_map<char, int> value = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    int result = value[s.back()];
    for (int i = s.length() - 2; i >= 0; i--) {
        result = value[s[i]] < value[s[i+1]] ? result - value[s[i]] : result + value[s[i]];
    }
    return result;
}
int main() {
    cout << romanToInt("III") << endl;
    cout << romanToInt("LVIII") << endl;
    cout << romanToInt("MCMXCIV") << endl;
}