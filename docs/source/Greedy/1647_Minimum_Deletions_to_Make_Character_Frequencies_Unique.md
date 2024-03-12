# Minimum Deletions to Make Character Frequencies Unique
% Medium
## Problem statement

[^url]A string `s` is considered "good" if there are no two different characters in the string that have the same frequency, meaning each character appears a unique number of times.

You're given a string `s`, and your task is to determine the minimum number of characters you need to delete from `s` to make it a "good" string.

The frequency of a character in a string is the count of times that character appears in the string. For instance, in the string `"aab"`, the frequency of `'a'` is `2`, and the frequency of `'b'` is `1`.

[^url]: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/ 
### Example 1
```text
Input: s = "aab"
Output: 0
Explanation: s is already good.
```

### Example 2
```text
Input: s = "aaabbbcc"
Output: 2
Explanation: You can delete two 'b's resulting in the good string "aaabcc".
Another way is to delete one 'b' and one 'c' resulting in the good string "aaabbc".
```

### Example 3
```text
Input: s = "ceabaacb"
Output: 2
Explanation: You can delete both 'c's resulting in the good string "eabaab".
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
``` 

### Constraints

* `1 <= s.length <= 10^5`.
* `s` contains only lowercase English letters.

## Solution: Delete the frequencies in sorted order
Your goal is to make all the frequencies be different.

One way of doing that is by sorting the frequencies and performing the deletion.

### Example 4
For `s = "ceaacbb"`, the frequencies of the characters are: `freq['a'] = 2, freq['b'] = 2, freq['c'] = 2` and `freq['e'] = 1`. They are already in sorted order.

* Let the current frequency be the first frequency `freq['a'] = 2`.
* The next frequency is `freq['b'] = 2`, equal to the current frequency. Delete one appearance to make the current frequency be `1`.
* The next frequency is `freq['c'] = 2`, bigger than the current frequency. Delete two appearances to make the current frequency be `0`.
* Because the current frequency is `0`, delete all appearances of the remaining frequencies, which is `freq['e'] = 1`.
* In total, there are `4` deletions.

### Code
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int minDeletions(string& s) {
    // map 'a'->0, 'b'->1, ..,'z'->25
    vector<int> freq(26, 0);
    for (char& c: s) {
        // count the frequency of character c
        freq[c - 'a']++;
    }
    // sort freq in descending order
    sort(freq.begin(), freq.end(), greater<int>());
    int deletion = 0;
    int currentFreq = freq.at(0); // start with the max frequency
    for (int i = 1; i < freq.size() && freq.at(i) > 0; i++) {
        if (currentFreq == 0) {
            // delete all remaining characters
            deletion += freq.at(i);
        } else if (freq[i] >= currentFreq) {
            // delete just enough to make the freq[i] < currentFreq
            deletion += freq.at(i) - currentFreq + 1;
            currentFreq--;
        } else {
            // do not delete on freq[i] < currentFreq
            currentFreq = freq.at(i);
        }
    }
    return deletion;
}
int main() {
    cout << minDeletions("aab") << endl;
    cout << minDeletions("aaabbbcc") << endl;
    cout << minDeletions("ceabaacb") << endl;
}
```
```text
Output:
0
2
2
```

### Complexity

* Runtime: `O(N)`, where `N = s.length`;
* Extra space: `O(1)`.

## Conclusion

The problem of determining the minimum number of deletions required to make character frequencies unique can be efficiently solved by counting the frequencies of characters and iteratively adjusting the frequencies to ensure uniqueness. 

This solution achieves this by first counting the frequencies of characters and then sorting them in descending order. By iteratively processing the sorted frequencies, the solution ensures that each character frequency is unique while minimizing the number of deletions required.

## Exercise
- Minimum Deletions to Make Array Beautiful[^ex].

[^ex]: https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/