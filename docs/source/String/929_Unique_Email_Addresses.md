# Unique Email Addresses
% Easy
## Problem statement

[^url]Each valid email address is composed of a local name and a domain name, separated by the `'@'` sign. The local name may contain lowercase letters, one or more `'.'` characters, and a plus `'+'` sign. However, the rules for dots and the plus sign do not apply to the domain name.

For example, in the email `"alice@leetcode.com"`, `"alice"` is the local name, and `"leetcode.com"` is the domain name.

If you insert periods `'.'` between certain characters in the local name, the email will still be forwarded to the same address without the dots in the local name. This rule does not apply to the domain name.

For example, `"alice.z@leetcode.com"` and `"alicez@leetcode.com"` both forward to the same email address.

If you include a plus `'+'` sign in the local name, everything after the first plus sign is ignored, allowing for email filtering. This rule also does not apply to the domain name.

For example, `"m.y+name@email.com"` will be forwarded to `"my@email.com"`.

It is possible to use both of these rules at the same time.

Given an array of strings `emails`, where each element is an email address to which an email is sent, your task is to determine the number of different addresses that will actually receive the emails after applying the rules described above.

[^url]: https://leetcode.com/problems/unique-email-addresses/ 
### Example 1
```text
Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.
```

### Example 2
```text
Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
Output: 3
``` 

### Constraints

* `1 <= emails.length <= 100`.
* `1 <= emails[i].length <= 100`.
* `emails[i]` consist of lowercase English letters, `'+'`, `'.'` and `'@'`.
* Each `emails[i]` contains exactly one `'@'` character.
* All local and domain names are non-empty.
* Local names do not start with a `'+'` character.
* Domain names end with the `".com"` suffix.

## Solution 1: Removing the ignored characters
Do exactly the steps the problem describes:

1. Extract the local name.
2. Ignore all characters after `'+'` in it.
3. Ignore all `'.'` in it.
4. Combine the local name with the domain one to form the clean email address.

### Code
```cpp
#include<string>
#include<iostream>
#include<vector>
#include <unordered_set>
using namespace std;
int numUniqueEmails(const vector<string>& emails) {
    unordered_set<string> s;
    for (auto& e: emails) {
        auto apos = e.find('@');

        // extract the local name
        string local = e.substr(0, apos);

        // ignore all characters after '+'
        local = local.substr(0, local.find('+'));   
        auto it = local.find('.');
        while (it != string::npos) {
            // remove each '.' found in local
            local.erase(it, 1);
            it = local.find('.');
        }
        // combine local name with domain one
        s.insert(local + e.substr(apos));
    }
    return s.size();
}
int main() {
    vector<string> emails{"test.email+alex@leetcode.com",
                        "test.e.mail+bob.cathy@leetcode.com",
                        "testemail+david@lee.tcode.com"};
    cout << numUniqueEmails(emails) << endl;
    emails = {"a@leetcode.com","b@leetcode.com","c@leetcode.com"};
    cout << numUniqueEmails(emails) << endl;
    emails = {"test.email+alex@leetcode.com","test.email.leet+alex@code.com"};
    cout << numUniqueEmails(emails) << endl;
}
```
```text
Output:
2
3
2
```

This solution parses a list of email addresses, normalizes each email address by removing periods and ignoring characters after the plus sign in the local name, and then counts the number of unique email addresses. The use of an unordered set ensures that only unique email addresses are counted.

### Complexity
* Runtime: `O(N*M^2)`, where `N = emails.length` and `M = max(emails[i].length)`. Explanation: you loop over `N` emails. Then you might loop over the length of each email, `O(M)`, to remove the character `'.'`. The removal might cost `O(M)`.
* Extra space: `O(N*M)` (the set of emails).

## Solution 2: Building the clean email addresses from scratch
The runtime of removing characters in `std::string` is not constant. To avoid that complexity you can build up the clean email addresses from scratch.

### Code
```cpp
#include<string>
#include<iostream>
#include<vector>
#include <unordered_set>
using namespace std;
int numUniqueEmails(const vector<string>& emails) {
    unordered_set<string> s;
    for (auto& e: emails) {
        string address; 
        int i = 0;
        // the local name ends here
        while (e[i] != '@' && e[i] != '+') {
            // ignore each '.' found
            if (e[i++] == '.') {
                continue;
            }
            // add valid characters to local name
            address += e[i++];                  
        }
        // combine local name with domain one
        address += e.substr(e.find('@', i));    
        s.insert(address);
    }        
    return s.size();
}
int main() {
    vector<string> emails{"test.email+alex@leetcode.com",
                        "test.e.mail+bob.cathy@leetcode.com",
                        "testemail+david@lee.tcode.com"};
    cout << numUniqueEmails(emails) << endl;
    emails = {"a@leetcode.com","b@leetcode.com","c@leetcode.com"};
    cout << numUniqueEmails(emails) << endl;
    emails = {"test.email+alex@leetcode.com","test.email.leet+alex@code.com"};
    cout << numUniqueEmails(emails) << endl;
}
```
```text
Output:
2
3
2
```

### Complexity

* Runtime: `O(N*M)`, where `N = emails.length` and `M = max(emails[i].length)`.
* Extra space: `O(N*M)`.

## C++ Notes

* A `string` can be concatenated with a `char` and another `string` by `+` operator.

```cpp
std::string address = "name";
address += '@';             // "name@"
address += "domain.com";    // "name@domain.com"
```
* `string::substr(pos = 0, count = npos)`[^subs] returns the substring of length `count` starting from the position `pos` of the string `string`.

[^subs]: https://en.cppreference.com/w/cpp/string/basic_string/substr

```cpp
std::string address = "name@domain.com";
cout << address.substr(address.find('.'));      // ".com"
cout << address.substr(0, address.find('@'));   // "name"
```

* `string::find(char, pos=0)`[^find] returns the position of the first `char` which appears in the string `string` starting from `pos`.

[^find]: https://en.cppreference.com/w/cpp/string/basic_string/find

## High-performance C++

* Do not use `std::set` or `std::map` unless you want the keys to be *in order* (*sorted*). Use *unordered containers* like `std::unordered_set`[^uset] or `std::unordered_map`[^umap] instead. They use hashed keys for faster lookup.

* Do not blindly/lazily use `string.find(something)`. If you know where to start the search, use `string.find(something, pos)` with a **specific** `pos`.

[^uset]: https://en.cppreference.com/w/cpp/container/unordered_set
[^umap]: https://en.cppreference.com/w/cpp/container/unordered_map