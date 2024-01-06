# Unique Email Addresses

## [Problem statement](https://leetcode.com/problems/unique-email-addresses/)

Each valid email address is composed of a local name and a domain name, separated by the `'@'` sign. The local name may contain lowercase letters, one or more `'.'` characters, and a plus `'+'` sign. However, the rules for dots and the plus sign do not apply to the domain name.

For example, in the email `"alice@leetcode.com"`, `"alice"` is the local name, and `"leetcode.com"` is the domain name.

If you insert periods `'.'` between certain characters in the local name, the email will still be forwarded to the same address without the dots in the local name. This rule does not apply to the domain name.

For example, `"alice.z@leetcode.com"` and `"alicez@leetcode.com"` both forward to the same email address.

If you include a plus `'+'` sign in the local name, everything after the first plus sign is ignored, allowing for email filtering. This rule also does not apply to the domain name.

For example, `"m.y+name@email.com"` will be forwarded to `"my@email.com"`.

It is possible to use both of these rules at the same time.

Given an array of strings `emails`, where each element is an email address to which an email is sent, your task is to determine the number of different addresses that will actually receive the emails after applying the rules described above.
 
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
int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> s;
    for (auto e: emails) {
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

### Code explanation

1. The code uses an `unordered_set<string> s` to store unique email addresses. Sets automatically ensure that only unique elements are stored.

2. The code iterates through each email address in the `emails` vector. Inside the loop, it finds the position of the at-symbol (`'@'`) in the current email address and stores it in the variable `apos`. This position is used to separate the local name from the domain.

3. The code extracts the local name of the email address using `e.substr(0, apos)`. The local name is the part of the email address before the `'@'` symbol.

4. It further processes the local name to remove characters after the plus sign (`'+'`). It uses `local.find('+')` to find the position of the plus sign within the local name and then truncates the local name to exclude characters after the plus sign using `local = local.substr(0, local.find('+'))`.

5. The code removes periods (`'.'`) from the local name. It initializes an iterator `it` to find the position of periods within the local name and then enters a loop that continues until no more periods are found. Inside the loop, it uses `local.erase(it, 1)` to remove each period from the local name.

6. After normalizing the local name, the code combines it with the domain name using `s.insert(local + e.substr(apos))` and inserts the result into the set `s`. This effectively combines the normalized local name with the domain name and adds it to the set of unique email addresses.

7. After processing all the email addresses, the code returns the size of the set `s`. The size of the set represents the number of unique email addresses after applying the normalization rules.

In summary, this code parses a list of email addresses, normalizes each email address by removing periods and ignoring characters after the plus sign in the local name, and then counts the number of unique email addresses. The use of an unordered set ensures that only unique email addresses are counted.

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
int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> s;
    for (auto e: emails) {
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

### Code explanation

1. The code uses an `unordered_set<string> s` to store unique email addresses. Sets automatically ensure that only unique elements are stored.

2. The code iterates through each email address in the `emails` vector. Inside the loop, it initializes an empty string `address` to store the normalized email address.

   - It also initializes an integer `i` to 0, which represents the current character position in the email address string `e`.

   - The code then enters a loop that continues until it encounters the at-symbol (`'@'`) or a plus sign (`'+'`). This loop serves to process the local name and exclude periods (`'.'`) from it.

   - Inside the loop, it first checks if the current character is a period (`'.'`). If it is, the code continues to the next character, effectively ignoring the period.

   - If the current character is not a period, it adds the character to the `address` string and increments the character position `i`.

   - After the loop, the `address` string contains the normalized local name.

3. After normalizing the local name, the code combines it with the domain name using `address += e.substr(e.find('@', i))`. This effectively combines the normalized local name with the domain name and adds it to the set `s`.

4. After processing all the email addresses, the code returns the size of the set `s`. The size of the set represents the number of unique email addresses after applying the normalization rules.


### Complexity
In summary, this code parses a list of email addresses, normalizes each email address by removing periods and ignoring characters after the plus sign in the local name, and then counts the number of unique email addresses. The use of an unordered set ensures that only unique email addresses are counted. This solution achieves the same result as the previous solution but uses a different approach to process the email addresses.

* Runtime: `O(N*M)`, where `N = emails.length` and `M = max(emails[i].length)`.
* Extra space: `O(N*M)`.

## C++ Notes

* A `string` can be concatenated with a `char` and another `string` by `+` operator.

```cpp
std::string address = "name";
address += '@';             // "name@"
address += "domain.com";    // "name@domain.com"
```
* [string::substr(pos = 0, count = npos)](https://en.cppreference.com/w/cpp/string/basic_string/substr) returns the substring of length `count` starting from the position `pos` of the string `string`.

```cpp
std::string address = "name@domain.com";
cout << address.substr(address.find('.'));      // ".com"
cout << address.substr(0, address.find('@'));   // "name"
```

* [string::find(char, pos=0)](https://en.cppreference.com/w/cpp/string/basic_string/find) returns the position of the first `char` which appears in the string `string` starting from `pos`.

## High-performance C++

* Do not use `std::set` or `std::map` unless you want the keys to be *in order* (*sorted*). Use *unordered containers* like [std::unordered_set](https://en.cppreference.com/w/cpp/container/unordered_set) or [std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map) instead. They use hashed keys for faster lookup.

* Do not blindly/lazily use `string.find(something)`. If you know where to start the search, use `string.find(something, pos)` with a **specific** `pos`.

