#include <iostream>
#include <stack>
using namespace std;

//! @param s a string of characters '(', ')', '[', ']', '{', '}'
//! @return true if the brackets in s are open and closed properly. 
//! @author Nhut Nguyen
bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else if (stk.empty()) {
            return false;
        } else if  (c == ')' && stk.top() != '(' ||
                    c == ']' && stk.top() != '[' ||
                    c == '}' && stk.top() != '{') {
            return false;
        } else {
            stk.pop();
        }
    }
    return stk.empty();
}

int main() {
    cout << isValid("()") << endl;
    cout << isValid("(){}[]") << endl;
    cout << isValid("(]") << endl;
    cout << isValid("([)]") << endl;
}