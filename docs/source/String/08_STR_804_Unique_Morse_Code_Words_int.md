# Unique {index}`Morse Code` Words

## [Problem statement](https://leetcode.com/problems/unique-morse-code-words/)

The problem involves the International Morse Code, which defines a standard way to encode letters with dots and dashes. Each English letter corresponds to a specific sequence in Morse Code, and a full table mapping each letter is provided.

For instance, `'a'` is encoded as `".-"`, `'b'` as `"-..."`, and so on.

The full table for the `26` letters of the English alphabet is given below:

```text
[".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
"....", "..", ".---", "-.-", ".-..", "--", "-.",
"---", ".--.", "--.-", ".-.", "...", "-", "..-",
"...-", ".--", "-..-", "-.--", "--.."]
```

You are given an array of strings named `words`, where each word can be represented as a concatenation of the Morse code for each of its letters. For example, the word `"cab"` can be represented as `"-.-..--..."`, which is the concatenation of `"-.-."`, `".-"`, and `"-..."`. This concatenated Morse code representation is referred to as the "transformation" of a word.

Your task is to count the number of different transformations that can be obtained from all the words in the given array.

### Example 1
```text
Input: words = ["gin","zen","gig","msg"]
Output: 2
Explanation: The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."
There are 2 different transformations: "--...-." and "--...--.".
```

### Example 2
```text
Input: words = ["a"]
Output: 1
``` 

### Constraints

* `1 <= words.length <= 100`.
* `1 <= words[i].length <= 12`.
* `words[i]` consists of lowercase English letters.

## Solution: Store the transformations in a set

### Code
```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int uniqueMorseRepresentations(vector<string>& words) 
{
    vector<string> morse{
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        "....", "..", ".---", "-.-", ".-..", "--", "-.",
        "---", ".--.", "--.-", ".-.", "...", "-", "..-",
        "...-", ".--", "-..-", "-.--", "--.."
    };
    unordered_set<string> transformations;
    for (string& w : words) 
    {
        string s{""};
        for (char& c : w) 
        {
            s += morse[c - 'a'];
        }
        transformations.insert(s);
    }
    return transformations.size();
}
int main() 
{
    vector<string> words{"gin","zen","gig","msg"};
    cout << uniqueMorseRepresentations(words) << endl;
    words = {"a"};
    cout << uniqueMorseRepresentations(words) << endl;
}
```
```text
Output:
2
1
```

### Code explanation

1. The solution begins with a predefined mapping of lowercase English letters to their corresponding Morse code representations. The Morse code representations are stored in a vector called `morse`.

2. An `unordered_set<string> transformations` is used to store the unique Morse code representations generated from the input words. This set will automatically ensure that only unique representations are stored.

3. The code iterates through each word in the `words` vector. For each word, it initializes an empty string `s` to store the Morse code representation of that word.

4. It then iterates through each character in the word. For each character `c` in the word, it appends the corresponding Morse code representation (retrieved from the `morse` vector) for that character to the `s` string. The mapping is accessed using `morse[c - 'a']`.

5. After constructing the Morse code representation for the current word, it inserts the `s` string into the `transformations` set. If `s` is already present in the set, it will not be added again since sets only allow unique elements.

6. After processing all the words, the size of the `transformations` set is returned as the result. The size of the set corresponds to the number of unique Morse code representations generated from the input words.


### Complexity
This solution converts each word into Morse code based on a predefined mapping and uses an unordered set to keep track of unique representations. By inserting each representation into the set, it automatically filters out duplicates. The final result is the size of the set, which represents the number of unique Morse code representations among the input words. 

* Runtime: `O(N*M)`, where `N = words.length` and `M = words[i].length`.
* Extra space: `O(N)`.
