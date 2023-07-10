# Find and Replace Pattern

## [Problem statement](https://leetcode.com/problems/find-and-replace-pattern/)

Given a list of strings `words` and a string `pattern`, return a list of `words[i]` that match `pattern`. You may return the answer in any order.

A word matches the pattern if there exists a permutation of letters `p` so that after replacing every letter `x` in the pattern with `p(x)`, we get the desired word.

Recall that a permutation of letters is a bijection from letters to letters: every letter maps to another letter, and no two letters map to the same letter.

 

### Example 1
```text
Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b -> e, ...}. 
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a permutation, since a and b map to the same letter.
```
### Example 2
```text
Input: words = ["a","b","c"], pattern = "a"
Output: ["a","b","c"]
``` 

### Constraints

* `1 <= pattern.length <= 20`.
* `1 <= words.length <= 50`.
* `words[i].length == pattern.length`.
* `pattern` and `words[i]` are lowercase English letters.

## Solution: Construct the bijection and check the condition

### Code

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> result;  
    // need two maps for the bijection
    unordered_map<char,char> w_to_p, p_to_w;
    int i;
    for (string& w : words) {
        w_to_p.clear();
        p_to_w.clear();
        i = 0;
        while (i < w.length()) {
            if (w_to_p.find(w[i]) != w_to_p.end()) {
                // w[i] was mapped to some letter x
                // but x != pattern[i]
                if (w_to_p[w[i]] != pattern[i]) {
                    break;
                }
            } else {
                if (p_to_w.find(pattern[i]) != p_to_w.end()) {
                    // w[i] was not mapped to any letter yet
                    // but pattern[i] was already mapped to some letter
                    break;
                }
                // build the bijection w[i] <-> pattern[i]
                w_to_p[w[i]] = pattern[i];
                p_to_w[pattern[i]] = w[i];
            }
            i++;
        }
        if (i == w.length()) {
            result.push_back(w);
        }
    }
    return result;
}
void printResult(const vector<string>& result) {
    cout << "[";
    for (const string& s : result) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<string> words{"abc","deq","mee","aqq","dkd","ccc"};
    auto result = findAndReplacePattern(words, "abb");
    printResult(result);
    words = {"a", "b", "c"};
    result = findAndReplacePattern(words, "abb");
    printResult(result);
}
```
```text
Output:
[mee,aqq,]
[a,b,c,]
```

### Complexity
* Runtime: `O(N*L)`, where `N = words.length` and `L = pattern.length`.
* Extra space: `O(1)` if `N` or `L` is very larger than 26. The maps `w_to_p` and `p_to_w` just map between 26 lowercase English letters.



