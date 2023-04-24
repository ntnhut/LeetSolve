#include <iostream>
#include <unordered_map>
using namespace std;

//! @return the integer value of s, e.g. 58.
//! @param s a roman numeral, e.g. s = "LVIII" 
//! @author Nhut Nguyen
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
    int i = s.length() - 1;
    int result = value[s[i--]];
    while (i >= 0) {
        if (value[s[i]] < value[s[i+1]]) {
            result -= value[s[i--]]; 
        } else {
            result += value[s[i--]];
        }
    }
    return result;
}

int main() {
    cout << romanToInt("III") << endl;
    cout << romanToInt("LVIII") << endl;
    cout << romanToInt("MCMXCIV") << endl;
}