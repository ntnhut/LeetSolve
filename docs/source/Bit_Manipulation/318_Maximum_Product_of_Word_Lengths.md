# Maximum Product of Word Lengths
% Medium 
## Problem statement

[^url]Given a string array `words`, return the maximum value of `length(word[i]) * length(word[j])` where the two words do not share common letters. If no such two words exist, return `0`.

[^url]: https://leetcode.com/problems/maximum-product-of-word-lengths/

### Example 1
```text
Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
```

### Example 2
```text
Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".
```

### Example 3
```text
Input: words = ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.
``` 

### Constraints

* `2 <= words.length <= 1000`.
* `1 <= words[i].length <= 1000`.
* `words[i]` consists only of lowercase English letters.

## Solution 1: Bruteforce

For each `words[i]`, for all `words[j]` with `j > i`, check if they do not share common letters and compute the product of their lengths.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxProduct(const vector<string>& words) {
    int maxP = 0;
    for (int i = 0; i < words.size(); i++) {
        // visited marks all letters that appear in words[i] 
        // words[i] consists of only 26 lowercase English letters
        vector<bool> visited(26, false);
        for (auto& c : words[i]) {
            // map 'a'->0, 'b'->1, .., 'z'->25
            visited[c - 'a'] = true;
        }
        // compare with all other words[j]         
        for (int j = i + 1; j < words.size(); j++) {
            bool found = false;
            for (auto& c : words[j]) {              
                if (visited[c - 'a']) {
                    // this words[j] has common letter with words[i]
                    found = true;
                    break;
                }
            }
            // if words[j] disjoints words[i]
            if (!found) {
                // compute and update max product of their lengths
                maxP = max(maxP, (int) (words[i].length() * words[j].length()));
            } 
        }
    }
    return maxP;
}
int main() {
    vector<string> words{"abcw","baz","foo","bar","xtfn","abcdef"};
    cout << maxProduct(words) << endl;
    words = {"a","ab","abc","d","cd","bcd","abcd"};
    cout << maxProduct(words) << endl;
    words = {"a","aa","aaa","aaaa"};
    cout << maxProduct(words) << endl;
}
```
```text
Output:
16
4
0
```

This solution checks for common characters between pairs of words to determine their product of lengths. 

It iterates through each pair of words in the input vector `words`, maintaining a boolean array `visited` to mark the presence of characters in each word. By comparing the characters of each pair of words, it identifies whether there are any common characters. If no common characters are found, it computes the product of the lengths of the two words and updates the maximum product accordingly. 

This approach optimizes the computation of the maximum product by efficiently checking for common characters between pairs of words without requiring additional space proportional to the length of the words.

### Complexity

* Runtime: `O(n^2 * m)`.
* Extra space: `O(1)`.

## Solution 2: Checking common letters using {index}`bit masking`

You can map a `words[i]` to the bit representation of an integer `n` by their characters like the following:

* If the word `words[i]` contains the letter `'a'`, the bit at position `0` of `n` is `1`.
* If the word `words[i]` contains the letter `'b'`, the bit at position `1` of `n` is `1`.
* ...
* If the word `words[i]` contains the letter `'z'`, the bit at position `25` of `n` is `1`.

Then to check if two words have common letters, you just perform the bitwise operator AND on them.

### Example 1:

* The word `"abcw"` is mapped to `00010000000000000000000111`.
* The word `"baz"` is mapped to `10000000000000000000000011`.
* `"abcw" & "baz" = 00000000000000000000000011`. This value is not zero, which means they have common letters.

This technique is called bit masking.

### Code 
```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxProduct(const vector<string>& words) {
    int maxP = 0;
    // initialize all elements of mask to 0
    vector<int> mask(words.size());
    for (int i = 0; i < words.size(); i++) {
        // mark all characters of word[i]
        for (auto& c : words[i]) {
            // map 'a'->0, 'b'->1, .., 'z'->25
            // set the bit at that mapped position of mask[i] to 1
            mask[i] |= 1 << (c - 'a');
        }        
        for (int j = 0; j < i; j++) {
            if ((mask[j] & mask[i]) == 0) {
                // there is no common bit between mask[j] and mask[i]
                maxP = max(maxP, (int) (words[i].length() * words[j].length()));
            } 
        }
    }
    return maxP;
}
int main() {
    vector<string> words{"abcw","baz","foo","bar","xtfn","abcdef"};
    cout << maxProduct(words) << endl;
    words = {"a","ab","abc","d","cd","bcd","abcd"};
    cout << maxProduct(words) << endl;
    words = {"a","aa","aaa","aaaa"};
    cout << maxProduct(words) << endl;
}
```
```text
Output:
16
4
0
```

This solution represents each word in the input vector `words` as a bitmask, where each bit represents the presence or absence of a character in the word. 

By iterating through the words and constructing their corresponding bitmasks, it encodes the character information. Then, by comparing the bitmasks of pairs of words, it identifies whether there are any common characters between them. If no common characters are found, it computes the product of the lengths of the two words and updates the maximum product accordingly. 

This approach optimizes the computation of the maximum product by using bitwise operations to efficiently check for common characters between pairs of words without requiring additional space proportional to the length of the words.

### Complexity

* Runtime: `O(n^2)`, where `n` is the number of words in the input vector.
* Extra space: `O(n)`.

## Tips

Utilizing bit manipulation techniques, such as bitmasking, can significantly optimize the comparison process for determining common characters between words. 

Solution 2 reduces the time complexity compared to brute force methods, particularly when dealing with large datasets, as it avoids nested loops and unnecessary character comparisons.