## 804. Unique Morse Code Words

### Problem statement
International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:

* `'a'` maps to `".-"`,
* `'b'` maps to `"-..."`,
* `'c'` maps to `"-.-."`, and so on.

For convenience, the full table for the `26` letters of the English alphabet is given below:

```plain
[".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
"....", "..", ".---", "-.-", ".-..", "--", "-.",
"---", ".--.", "--.-", ".-.", "...", "-", "..-",
"...-", ".--", "-..-", "-.--", "--.."]
```

Given an array of strings `words` where each word can be written as a concatenation of the Morse code of each letter.

* For example, `"cab"` can be written as `"-.-..--..."`, which is the concatenation of `"-.-."`, `".-"`, and `"-..."`. We will call such a concatenation the transformation of a word.

Return the number of different transformations among all words we have.

 

#### Example 1
```plain
Input: words = ["gin","zen","gig","msg"]
Output: 2
Explanation: The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."
There are 2 different transformations: "--...-." and "--...--.".
```

#### Example 2
```plain
Input: words = ["a"]
Output: 1
``` 

#### Constraints

* `1 <= words.length <= 100`.
* `1 <= words[i].length <= 12`.
* `words[i]` consists of lowercase English letters.

### Solution: Store the transformations in a set

#### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int uniqueMorseRepresentations(vector<string>& words) {
    vector<string> morse{".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                        "....", "..", ".---", "-.-", ".-..", "--", "-.",
                        "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                        "...-", ".--", "-..-", "-.--", "--.."};
    unordered_set<string> transformations;
    for (string& w : words) {
        string s{""};
        for (char& c : w) {
            s += morse[c - 'a'];
        }
        transformations.insert(s);
    }
    return transformations.size();
}
int main() {
    vector<string> words{"gin","zen","gig","msg"};
    cout << uniqueMorseRepresentations(words) << endl;
    words = {"a"};
    cout << uniqueMorseRepresentations(words) << endl;
}
```
```plain
Output:
2
1
```

#### Complexity
* Runtime: `O(N*M)`, where `N = words.length` and `M = words[i].length`.
* Extra space: `O(N)`.

### References
* [https://leetcode.com/problems/unique-morse-code-words/](https://leetcode.com/problems/unique-morse-code-words/)
* [https://www.leetsolve.com/804-unique-morse-code-words](https://www.leetsolve.com/804-unique-morse-code-words)