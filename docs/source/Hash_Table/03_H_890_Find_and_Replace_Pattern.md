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

### Code explanation

1. The code initializes an empty vector called `result`, which will store the words that match the given pattern.

2. Two unordered maps (`w_to_p` and `p_to_w`) are defined to establish the bijection between characters in words and characters in the pattern. These maps are used to track the mapping relationship between characters in a word and their corresponding characters in the pattern.

3. An integer variable `i` is declared to be used as an index to iterate through the characters of a word.

4. The code enters a loop that iterates through each word in the `words` vector using a range-based for loop.

5. Inside the loop, the maps `w_to_p` and `p_to_w` are cleared at the beginning of processing each word. This ensures that the maps are empty and ready to establish a new bijection for the current word.

6. The code enters another loop that iterates through the characters of the word.

7. Inside this loop, the code checks whether the character `w[i]` from the word has already been mapped to a character in the pattern:
   - If `w[i]` is found in the `w_to_p` map, it means that `w[i]` was previously mapped to some character (let's call it `x`) in the pattern. In this case, the code checks if `x` is not equal to `pattern[i]`. If `x` is not equal to `pattern[i]`, it means that `w[i]` cannot be mapped to `pattern[i]`, so the loop is terminated by `break`.
   - If `w[i]` is not found in the `w_to_p` map, the code checks whether `pattern[i]` has already been mapped to a character in the word:
     - If `pattern[i]` is found in the `p_to_w` map, it means that `pattern[i]` was previously mapped to some character in the word. In this case, the loop is terminated by `break`.
     - If neither `w[i]` nor `pattern[i]` is found in their respective maps, a bijection between `w[i]` and `pattern[i]` is established by adding entries to both maps.

8. After processing all characters of the current word, the code checks if `i` has reached the length of the word. If `i` equals `w.length()`, it means that a bijection has been successfully established for the entire word, and the word matches the pattern. In this case, the word is added to the `result` vector using `result.push_back(w);`.

9. After processing all words, the `result` vector contains all the words that match the pattern in terms of character bijection.

12. The function returns the `result` vector, which contains the matching words.

In summary, this code efficiently finds and returns words from a vector of strings that match a given pattern in terms of character bijection. It uses two unordered maps to establish and maintain the bijection while iterating through the characters of the words and the pattern. 

### Complexity
* Runtime: `O(NL)`, where `N = words.length` and `L = pattern.length`.
* Extra space: `O(1)`. The maps `w_to_p` and `p_to_w` just map between 26 lowercase English letters.



