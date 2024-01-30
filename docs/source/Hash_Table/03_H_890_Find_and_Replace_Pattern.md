# Find and Replace Pattern

## [Problem statement](https://leetcode.com/problems/find-and-replace-pattern/)

You are provided with a list of strings named `words` and a string named `pattern`. Your task is to find the strings from `words` that match the given `pattern`. The order in which you return the answers does not matter.

A word is considered to match the pattern if there is a mapping `p` of the letters such that, when each letter `x` in the pattern is replaced with `p(x)`, the word is formed.

Keep in mind that a permutation of letters is a one-to-one correspondence from letters to letters, where each letter is mapped to a distinct letter, and no two letters are mapped to the same letter. 

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
This solution efficiently finds and returns words from a vector of strings that match a given pattern in terms of character bijection. It uses two unordered maps to establish and maintain the bijection while iterating through the characters of the words and the pattern. 

### Complexity

* Runtime: `O(NL)`, where `N = words.length` and `L = pattern.length`.
* Extra space: `O(1)`. The maps `w_to_p` and `p_to_w` just map between 26 lowercase English letters.



