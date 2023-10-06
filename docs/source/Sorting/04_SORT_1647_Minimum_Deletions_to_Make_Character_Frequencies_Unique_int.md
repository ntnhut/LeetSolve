# Minimum Deletions to Make Character Frequencies Unique

## [Problem statement](https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/)

A string `s` is considered "good" if there are no two different characters in the string that have the same frequency, meaning each character appears a unique number of times.

You're given a string `s`, and your task is to determine the minimum number of characters you need to delete from `s` to make it a "good" string.

The frequency of a character in a string is the count of times that character appears in the string. For instance, in the string `"aab"`, the frequency of `'a'` is `2`, and the frequency of `'b'` is `1`.

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
int minDeletions(string s) {
    vector<int> freq(26, 0);
    for (char& c: s) {
        freq[c - 'a']++;
    }
    sort(freq.begin(), freq.end(), greater<int>());
    int deletion = 0;
    int currentFreq = freq.at(0);
    for (int i = 1; i < freq.size() && freq.at(i) > 0; i++) {
        if (currentFreq == 0) {
            deletion += freq.at(i);
        } else if (freq[i] >= currentFreq) {
            deletion += freq.at(i) - currentFreq + 1;
            currentFreq--;
        } else {
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

### Code explanation

1. The code initializes a vector `freq` of size 26 to represent the frequency of each lowercase letter in the English alphabet. It initializes all elements to 0.

2. It iterates through the characters in the input string `s`. For each character `c`, increment the corresponding frequency in the `freq` vector. This step calculates the frequency of each character in the string.

3. It sorts the `freq` vector in descending order using `greater<int>()` as the sorting comparator. This sorts the frequencies from highest to lowest.

4. It initializes two variables: `deletion` to keep track of the total deletions needed and `currentFreq` to keep track of the current frequency being processed.

5. It iterates through the sorted `freq` vector, starting from the second element (index 1):

   - If `currentFreq` becomes 0 (meaning there are no more characters with the current frequency), add the frequency of the current character to `deletion`. This is because you want to minimize the frequency and make it unique.

   - If the frequency of the current character (`freq[i]`) is greater than or equal to `currentFreq`, it implies that you need to reduce the frequency to `currentFreq - 1` and add the excess characters to `deletion`. The excess is calculated as `freq[i] - currentFreq + 1`. Decrease `currentFreq` accordingly.

   - If none of the above conditions apply, update `currentFreq` to the frequency of the current character since it becomes the new frequency to work with.

6. It returns the `deletion` value, which represents the minimum number of character deletions required to make all character frequencies unique.


### Complexity
This solution calculates the frequencies of characters in the input string, sorts them in descending order, and then iterates through them to determine the minimum deletions needed to achieve unique frequencies. 

* Runtime: `O(N)`, where `N = s.length`;
* Extra space: `O(1)`.


