# Excel Sheet Column Number

## [Problem statement](https://leetcode.com/problems/excel-sheet-column-number/)

Given a string `columnTitle` that represents the column title as appears in an Excel sheet, return its corresponding column number.

For example:
```text
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
...
``` 

### Example 1
```text
Input: columnTitle = "A"
Output: 1
```

### Example 2
```text
Input: columnTitle = "AB"
Output: 28
```

### Example 3
```text
Input: columnTitle = "ZY"
Output: 701
``` 

### Constraints

* `1 <= columnTitle.length <= 7`.
* `columnTitle` consists only of uppercase English letters.
* `columnTitle` is in the range `["A", "FXSHRXW"]`.

## Solution: Finding The Pattern

Let us write down some other `columnTitle` strings and its value.
```text
"A"   =  1
"Z"   =  26
"AA"  =  27
"AZ"  =  52
"ZZ"  =  702
"AAA" =  703
```

Then try to find the pattern
```text
"A"   =  1    =  1
"Z"   =  26   =  26
"AA"  =  27   =  26 + 1
"AZ"  =  52   =  26 + 26
"ZZ"  =  702  =  26*26 + 26
"AAA" =  703  =  26*26 + 26 + 1
```

If you map `'A' = 1, ..., 'Z' = 26`, the values can be rewritten as
```text
"A"   =  1    =  'A'
"Z"   =  26   =  'Z'
"AA"  =  27   =  26*'A' + 'A'
"AZ"  =  52   =  26*'A' + 'Z'
"ZZ"  =  702  =  26*'Z' + 'Z'
"AAA" =  703  =  26*26*'A' + 26*'A' + 'A'
```

In general the formula for a string `columnTitle = abcd` is
```text
abcd = 26^3*a + 26^2*b + 26*c + d,
```
where `a, b, c, d` are some uppercase English letters `A, ..., Z`.

Longer `columnTitle`s will have bigger leading exponents of `26`.

### Code
```cpp
#include <iostream>
using namespace std;
int titleToNumber(string columnTitle) {
    int column = 0; 
    for (char c : columnTitle) {
        // The ASCII value of 'A' is 65.
        column = 26*column + (c - 64); 
    }
    return column;
}
int main() {
    cout << titleToNumber("A") << endl;
    cout << titleToNumber("AB") << endl;
    cout << titleToNumber("ZY") << endl;
}
```
```text
Output:
1
28
701
```

### Code explanation

1. The code initializes an integer variable `column` to store the column number. This variable starts at 0 and will be updated as we process each character in `columnTitle`.

2. It iterates through each character `c` in the `columnTitle` string using a range-based for loop.

3. Inside the loop, it calculates the numeric value associated with the current character `c`. This is done using the formula `(c - 64)`. Here's why:
   - The ASCII value of `'A'` is 65.
   - To convert `'A'` to 1, `'B'` to 2, and so on, you need to subtract 64 from the ASCII value of the character.

4. The code multiplies the current value of `column` by 26 and then adds the calculated numeric value of the character. This step effectively accumulates the values for each character from left to right.

5. Once the loop finishes, the `column` variable will contain the numeric representation of the entire column title.

7. The code returns the `column` value, which represents the corresponding column number.

This algorithm works because Excel column titles follow a base-26 numbering system, where `'A'` corresponds to 1, `'B'` to 2, ..., `'Z'` to 26, `'AA'` to 27, `'AB'` to 28, and so on. 

### Complexity
The code efficiently calculates the decimal representation of the Excel column title by processing each character and updating the result. It has a time complexity of `O(N)`, where `N` is the length of `columnTitle`, as it iterates through the characters once, and a space complexity of `O(1)` since it uses a constant amount of extra space.

* Runtime: `O(N)`, where `N = columnTitle.length`.
* Extra space: `O(1)`.

### Implementation notes
1. There are many ways to compute the series
    ```text
    26^3*a + 26^2*b + 26*c + d.
    ```
    If you write it as 
    ```text
    26*(26*(26*(0 + a) + b) + c) + d,
    ```
    you get the loop in the code above.

2. To map `'A' = 1, ..., 'Z' = 26`, you can use their ASCII values (`'A' = 65, ..., 'Z' = 90`) minus `64`.
3. The parentheses around `(c - 64)` is needed. Otherwise the value of `columnTitle = "FXSHRXW"` makes `26*column + c` exceed the limit of `int` before it substracts `64`. 



