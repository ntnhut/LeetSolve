#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
const unordered_map<char, vector<char> > m{{'2', {'a', 'b', 'c'}},
                                        {'3', {'d', 'e', 'f'}},
                                        {'4', {'g', 'h', 'i'}},
                                        {'5', {'j', 'k', 'l'}},
                                        {'6', {'m', 'n', 'o'}},
                                        {'7', {'p', 'q', 'r', 's'}},
                                        {'8', {'t', 'u', 'v'}},
                                        {'9', {'w', 'x', 'y', 'z'}}};

void combination(const string_view& digits, int i, vector<string>& result) {
    if (i >= digits.length()) {
        return;
    }
    if (result.empty()) {
        result = {""};
    }
    vector<string> newResult;
    for (string& s : result) {
        for (auto& c : m.at(digits[i])) {
            newResult.push_back(s + c);
        }
    }
    result.swap(newResult);
    combination(digits, i + 1, result);
}

//! @return all possible letter combinations that the number could represent
//! @example "23" produces ["ad","ae","af","bd","be","bf","cd","ce","cf"]
//! @param digits a string containing digits from 2 to 9 on the telephone buttons.
//! @author Nhut Nguyen
vector<string> letterCombinations(string digits) {
    vector<string> result;
    combination(digits, 0, result);
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