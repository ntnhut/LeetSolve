# Excel Sheet Column Number
% Easy 
## Problem statement

[^url]Given a string `columnTitle` that represents the column title as appears in an Excel sheet, return its corresponding column number.

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

[^url]: https://leetcode.com/problems/excel-sheet-column-number/

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
int titleToNumber(const string& columnTitle) {
    int column = 0; 
    for (auto& c : columnTitle) {
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

The solution calculates the decimal representation of the Excel column title by processing each character and updating the result. 

### Complexity

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
3. The parentheses around `(c - 64)` is needed. Otherwise the value of `columnTitle = "FXSHRXW"` makes `26*column + c` exceed the limit of `int` before it subtracts `64`. 

## Exercise
- Excel Sheet Column Title[^ex].

[^ex]: https://leetcode.com/problems/excel-sheet-column-title/