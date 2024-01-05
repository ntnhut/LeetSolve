# Maximum Product of Word Lengths

## [Problem statement](https://leetcode.com/problems/maximum-product-of-word-lengths/)

Given a string array `words`, return the maximum value of `length(word[i]) * length(word[j])` where the two words do not share common letters. If no such two words exist, return `0`.

 

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
int maxProduct(vector<string>& words) {
    int maxP = 0;
    for (int i = 0; i < words.size(); i++) {
        vector<bool> visited(26, false);
        for (char c : words[i]) {
            visited[c - 'a'] = true;
        }        
        for (int j = i + 1; j < words.size(); j++) {
            bool found = false;
            for (char c : words[j]) {              
                if (visited[c - 'a']) {
                    found = true;
                    break;
                }
            }
            if (!found) {
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
### Code explanation

1. The code initializes a variable `maxP` to store the maximum product of word lengths, initially set to `0`.

2. It iterates through the words in the input vector `words` using a nested loop. The outer loop, indexed by `i`, iterates from `0` to `words.size() - 1`, and the inner loop, indexed by `j`, iterates from `i + 1` to `words.size() - 1`. This setup ensures that each pair of words is considered only once, avoiding unnecessary duplicate checks.

3. For each pair of words `words[i]` and `words[j]`, it follows these steps:
   - It initializes a boolean vector `visited` of size `26` (representing the English alphabet) with all values set to `false`. This vector will be used to mark the letters that exist in `words[i]`.
   - It iterates through each character `c` in `words[i]` and sets the corresponding element in the `visited` vector to `true`, indicating that the letter `c` exists in `words[i]`.
   - It then iterates through each character `c` in `words[j]` and checks if the corresponding element in the `visited` vector is already `true`. If it is, this means that a common letter exists between the two words, and it sets `found` to `true` and breaks out of the inner loop.
   - If `found` remains `false` after checking all characters in `words[j]`, it means that no common letters exist between `words[i]` and `words[j]`. In this case, it calculates the product of the lengths of `words[i]` and `words[j]` and updates `maxP` with the maximum of its current value and this product.

4. After completing the nested loops, it returns the final value of `maxP`, which represents the maximum product of the lengths of two words in the input vector with no common letters.


### Complexity
The code efficiently compares pairs of words to find the maximum product of their lengths, considering whether they share any common letters. The time complexity of this solution is `O(n^2 * m)`, where `n` is the number of words in the input vector and `m` is the average length of the words.

* Runtime: `O(n^2 * m)`.
* Extra space: `O(1)`.

## Solution 2: Checking common letters using {index}`bit masking`

You can map a `words[i]` to the bit representation of an integer `n` by their characters like the following:

* If the word `words[i]` contains the letter `'a'`, the bit at position `0` of `n` is `1`.
* If the word `words[i]` contains the letter `'b'`, the bit at position `1` of `n` is `1`.
* ...
* If the word `words[i]` contains the letter `'z'`, the bit at position `25` of `n` is `1`.

Then to check if two words have common letters, you just perform the bitwise operator AND on them.

For Example 1:

* The word `"abcw"` is mapped to `00010000000000000000000111`.
* The word `"baz"` is mapped to `10000000000000000000000011`.
* `"abcw" & "baz" = 00000000000000000000000011`. This value is not zero, which means they have common letters.

This technique is called bit masking.

### Code 
```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxProduct(vector<string>& words) {
    int maxP = 0;
    vector<int> mask(words.size());
    for (int i = 0; i < words.size(); i++) {
        for (char c : words[i]) {
            mask[i] |= 1 << (c - 'a');
        }        
        for (int j = 0; j < i; j++) {
            if ((mask[j] & mask[i]) == 0) {
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

### Code explanation

1. The code initializes an integer variable `maxP` to store the maximum product of word lengths, initially set to `0`.

2. It creates a vector of integers called `mask`, which will be used for bit masking. The `mask` vector is of the same size as the input vector `words`, with one element for each word.

3. It iterates through the words in the input vector `words` using a single loop, indexed by `i`. This loop iterates from `0` to `words.size() - 1`.

4. For each word `words[i]`, it follows these steps:
   - It initializes an integer `mask[i]` to `0`. This integer will serve as a bitmask to represent the letters present in the word.
   - It iterates through each character `c` in `words[i]` and sets the corresponding bit in `mask[i]` to `1`. This is achieved using bitwise left shift (`<<`) and bitwise OR (`|`) operations to set the corresponding bit for each character in the word.
   
5. After calculating the bitmask for the current word, it enters a nested loop that iterates through the words before the current word, indexed by `j`. This inner loop iterates from `0` to `i - 1`.

6. For each pair of words `words[i]` and `words[j]`, it checks if the bitwise AND (`&`) operation between the masks `mask[i]` and `mask[j]` results in `0`. If this condition is met, it means that there are no common letters between the two words, and it calculates the product of the lengths of `words[i]` and `words[j]`. It updates `maxP` with the maximum of its current value and this product.

7. After completing the loop, it returns the final value of `maxP`, which represents the maximum product of the lengths of two words in the input vector with no common letters.


### Complexity
By using bit masking to represent the presence of letters in words, this code avoids the need for nested loops and efficiently checks for common letters between pairs of words. As a result, it has a time complexity of `O(n^2)`, where `n` is the number of words in the input vector.

* Runtime: `O(n^2)`.
* Extra space: `O(n)`.

