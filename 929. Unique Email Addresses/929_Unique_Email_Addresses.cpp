#include<string>
#include<iostream>
#include<vector>
#include <unordered_set>
using namespace std;

//! @param emails an array of strings containing exactly one character '@'.
//! @return the number of different addresses after removing ignored characters,
//!         in the local name before '@'. 
//!         Ignored characters are the character '.' and the ones behind '+'.
//! @author Nhut Nguyen
int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> s;
    for (auto e: emails) {
        string address; 
        int i = 0;
        while (e[i] != '@' && e[i] != '+') {    // the local name ends here
            if (e[i++] == '.') {                // ignore each '.' found
                continue;
            }
            address += e[i++];                  // add valid characters to local name
        }
        address += e.substr(e.find('@', i));    // combine local name with domain one
        s.insert(address);
    }        
    return s.size();
}
int main() {
    vector<string> emails = {"test.email+alex@leetcode.com",
                            "test.e.mail+bob.cathy@leetcode.com",
                            "testemail+david@lee.tcode.com"};
    cout << numUniqueEmails(emails) << endl; // 2
    emails = {"a@leetcode.com","b@leetcode.com","c@leetcode.com"};
    cout << numUniqueEmails(emails) << endl; // 3
    emails = {"test.email+alex@leetcode.com","test.email.leet+alex@code.com"};
    cout << numUniqueEmails(emails) << endl; // 2
}