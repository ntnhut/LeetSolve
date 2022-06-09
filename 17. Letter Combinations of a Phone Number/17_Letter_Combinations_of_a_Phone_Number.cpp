#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

void combination(string& digits, unordered_map<char, vector<char> >& m, 
        int i, vector<string>& result) {
    if (i >= digits.length()) {
        return;
    }
    vector<string> newResult;
    if (result.empty()) {
        result= {""};
    }
    for (string& s : result) {
        for (auto c : m[digits[i]]) {
            newResult.push_back(s + c);
        }
    }
    result.swap(newResult);
    combination(digits, m, i + 1, result);
}

vector<string> letterCombinations(string digits) {
    unordered_map<char, vector<char> > m;
    m['2'] = {'a', 'b', 'c'};
    m['3'] = {'d', 'e', 'f'};
    m['4'] = {'g', 'h', 'i'};
    m['5'] = {'j', 'k', 'l'};
    m['6'] = {'m', 'n', 'o'};
    m['7'] = {'p', 'q', 'r', 's'};
    m['8'] = {'t', 'u', 'v'};
    m['9'] = {'w', 'x', 'y', 'z'};
    vector<string> result;
    combination(digits, m, 0, result);
    return result;
}
void printResult(vector<string>& result) {
    cout << "[";
    for (string& s : result) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<string> result = letterCombinations("23");
    printResult(result);
    result = letterCombinations("");
    printResult(result);
    result = letterCombinations("2");
    printResult(result);
}