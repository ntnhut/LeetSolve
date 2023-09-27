# Best Time to Buy and Sell Stock

## [Problem statement](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

You are given an array `prices` where `prices[i]` is the price of a given stock on the `i-th` day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

### Example 1
```text
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
```
### Example 2
```text
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
``` 

### Constraints

* `1 <= prices.length <= 10^5`.
* `0 <= prices[i] <= 10^4`.

## Solution 1: Bruteforce

For each day `i`, find the day `j > i` that gives maximum profit.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxProfit(vector<int>& prices) {
    int maxProfit = 0;
    for (int i = 0; i < prices.size(); i++) {        
        for (int j = i + 1; j < prices.size(); j++) {
            if (prices[j] > prices[i]) {
                maxProfit = max(maxProfit, prices[j] - prices[i]);
            }
        }
    }
    return maxProfit;
}
int main() {
    vector<int> prices{7,1,5,3,6,4};
    cout << maxProfit(prices) << endl;
    prices = {7,6,4,3,1};
    cout << maxProfit(prices) << endl;
}
```
```text
Output:
5
0
```
### Code explanation

1. The code initializes a variable `maxProfit` to 0. This variable will be used to store the maximum profit that can be achieved.

2. The outer loop (indexed by `i`) iterates through the `prices` array from the beginning, representing the day of purchase.

3. The inner loop (indexed by `j`) iterates through the `prices` array starting from the day after the current day (`i+1`), representing the day of sale.

4. The code checks if the price on day `j` is greater than the price on day `i`. If it is, it means a profit can be made by buying on day `i` and selling on day `j`.

5. It calculates the profit by subtracting the price on day `i` from the price on day `j`.

6. The code updates the `maxProfit` variable with the maximum of its current value and the profit calculated in step 5.

7. It continues the inner loop to consider all possible selling days for the given buying day (`i`) and continues the outer loop to consider all possible buying days.

8. Once both loops are complete, the code returns the `maxProfit`, which represents the maximum profit achievable by buying and selling the stock.


### Complexity
This code essentially uses a brute force approach to find the maximum profit. It compares the profit obtained by buying on each day with selling on all subsequent days and keeps track of the maximum profit found. The time complexity of this code is `O(N^2)`, where `N` is the number of days (elements in `prices`), because it involves nested loops. The space complexity is `O(1)` as it uses a constant amount of extra space.

* Runtime: `O(N^2)`, where `N = prices.length`.
* Extra space: `O(1)`.

## Solution 2: Smallest and largest prices

Given a past day `i`, the future day `j > i` that gives the maximum profit is the day that has the largest price which is bigger than `prices[i]`.

Conversely, given a future day `j`, the past day `i < j` that gives the maximum profit is the day with the smallest price.

### Code
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int maxProfit(vector<int>& prices) {
    int maxProfit = 0;
    int i = 0;
    while (i < prices.size()) {
        while (i < prices.size() - 1 && prices[i] >= prices[i + 1]) {
            i++;
        }
        auto imax = max_element(prices.begin() + i, prices.end());
        auto imin = min_element(prices.begin() + i, imax);
        maxProfit = max(maxProfit, *imax - *imin);
        i = distance(prices.begin(), imax) + 1;
    }
    return maxProfit;
}
int main() {
    vector<int> prices{7,1,5,3,6,4};
    cout << maxProfit(prices) << endl;
    prices = {7,6,4,3,1};
    cout << maxProfit(prices) << endl;
    prices = {2,4,1,7};
    cout << maxProfit(prices) << endl;
    prices = {2,4,1};
    cout << maxProfit(prices) << endl;
}
```
```text
Output:
5
0
6
2
```

### Code explanation

1. The code initializes a variable `maxProfit` to 0. This variable will be used to store the maximum profit that can be achieved.

2. It starts a `while` loop that continues as long as the current day `i` is within the bounds of the `prices` array.

3. Within the loop, there is an inner `while` loop that finds the local minimum point for buying the stock. It checks if the current price (`prices[i]`) is greater than or equal to the price of the next day (`prices[i + 1]`). If so, it increments `i` to move to the next day. This inner loop helps to skip over periods of decreasing stock prices.

4. Once a potential buying day is found (where the price is less than the next day), it searches for the optimal selling day by using `max_element` and `min_element` functions. It looks for the maximum price (`imax`) after the buying day and the minimum price (`imin`) between the buying day and the maximum price.

5. The code calculates the profit that can be obtained by subtracting the minimum price (`*imin`) from the maximum price (`*imax`) found in the range.

6. It updates the `maxProfit` variable with the maximum of its current value and the profit calculated in step 6.

7. The code updates `i` to the index of the maximum price (`imax`) plus 1 to avoid considering overlapping intervals.

8. It continues the outer `while` loop to find other potential buying days and calculate profits.

9. Once the outer loop is complete, the code returns the `maxProfit`, which represents the maximum profit achievable by buying and selling the stock.

### Complexity
This code optimally finds the maximum profit by iterating through the array only once, avoiding the need for nested loops. The time complexity of this code is `O(N)`, where `N` is the number of days (elements in `prices`), making it more efficient than the brute force approach. The space complexity is `O(1)` as it uses only a constant amount of extra space.

* Runtime: `O(N)`, where `N = prices.length`.
* Extra space: `O(1)`.

## Solution 3: Only the smallest price

Given a future day `j`, the past day `i` that gives the maximum profit is the day with minimum price.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
int maxProfit(vector<int>& prices) {
    int maxProfit = 0;
    int minPrice = prices[0];
    for (int i = 1; i < prices.size(); i++)  {
        minPrice = min(minPrice, prices[i]);
        maxProfit = max(maxProfit, prices[i] - minPrice);
    }
    return maxProfit;
}
int main() {
    vector<int> prices{7,1,5,3,6,4};
    cout << maxProfit(prices) << endl;
    prices = {7,6,4,3,1};
    cout << maxProfit(prices) << endl;
    prices = {2,4,1,7};
    cout << maxProfit(prices) << endl;
    prices = {2,4,1};
    cout << maxProfit(prices) << endl;
}
```
```text
Output:
5
0
6
2
```

### Code explanation

1. The code initializes `maxProfit` to 0. This variable will store the maximum profit that can be achieved.

2. It initializes `minPrice` to the first element of the `prices` array. `minPrice` represents the minimum price of the stock encountered so far.

3. The code iterates through the `prices` array starting from the second element (index 1) and continuing until the last element.

4. For each element at index `i`, it updates `minPrice` to be the minimum of its current value (`minPrice`) and the stock price at index `i`. This step ensures that `minPrice` always tracks the lowest price seen so far.

5. The code calculates the potential profit that can be obtained on the current day by subtracting `minPrice` (the buying price) from the stock price at index `i`.

6. It updates `maxProfit` to be the maximum of its current value (`maxProfit`) and the profit calculated in step 5. This step keeps track of the maximum profit seen so far.

7. After the loop completes, `maxProfit` will contain the maximum profit that can be achieved by buying and selling the stock within the given array.

### Complexity
This code has a time complexity of `O(N)`, where `N` is the number of days (elements in `prices`). It efficiently computes the maximum profit by iterating through the array only once, maintaining the minimum buying price and updating the maximum profit accordingly. The space complexity is `O(1)` as it uses only a constant amount of extra space to store the variables `maxProfit` and `minPrice`.

* Runtime: `O(N)`, where `N = prices.length`.
* Extra space: `O(1)`.



