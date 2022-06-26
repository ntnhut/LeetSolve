# 1423. Maximum Points You Can Obtain from Cards

## Problem statement

There are several cards arranged in a row, and each card has an associated number of points. The points are given in the integer array `cardPoints`.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly `k` cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array `cardPoints` and the integer `k`, return the maximum score you can obtain.

 

### Example 1
```plain
Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
```

### Example 2
```plain
Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.
```

### Example 3
```plain
Input: cardPoints = [9,7,7,9,7,7,9], k = 7
Output: 55
Explanation: You have to take all the cards. Your score is the sum of points of all cards.
``` 

### Constraints

* `1 <= cardPoints.length <= 10^5`.
* `1 <= cardPoints[i] <= 10^4`.
* `1 <= k <= cardPoints.length`.

## Solution 1: Compute the sums of `k` consecutive cards of interest

Assume there are `N` cards in `cardPoints`. You might be interested in only `2k` cards in this problem. 

Any card you take is either in the first `k` cards `cardPoints[0, ..., k-1]` or in the last `k` cards `cardPoints[N-k, ..., N-1]`.

If you concatenate the last part with the first one like this `cardPoints[N-k, ..., N-1, 0, ..., k-1]`, the problem turns into computing the maximum sum of the `k` consecutive cards in that new array.

### Example 1
For `cardPoints = [1,2,3,4,5,6,1]` and `k = 3`, concatenating the last `3` cards with the first `3` cards you get the array `[5,6,1,1,2,3,4]`.

The maximum sum of the `3` consecutive cards is `sum([5,6,1]) = 12`.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int maxScore(vector<int>& cardPoints, int k) {
    vector<int> cards(cardPoints.end() - k, cardPoints.end());
    cards.insert(cards.end(), cardPoints.begin(), cardPoints.begin() + k);
    int maxSum = 0;
    for (int i = 0; i <= k; i++) {
        int sum = 0;
        for (int j = 0; j < k; j++) {
            sum += cards[i + j];
        }
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
int main() {
    vector<int> cardPoints{1,2,3,4,5,6,1};
    cout << maxScore(cardPoints, 3) << endl;
    cardPoints = {2,2,2};
    cout << maxScore(cardPoints, 2) << endl;
    cardPoints = {9,7,7,9,7,7,9};
    cout << maxScore(cardPoints, 7) << endl;
}
```
```plain
Output:
12
4
55
```

### Complexity
* Runtime: `O(k^2)`.
* Extra space: `O(2k)`.

## Solution 2: Improve the performance

When `k` is large (it can equal `cardPoints.length`), the solution above is slow due to runtime complexity `O(k^2)`.

It is because there are many recomputations when computing the `sum` of each `k` consecutive cards.

You can save this runtime by keeping the common `(k-1)`-sum between two neighbor `k`-sums.

### Example 1
The sum `6 + 1` are computed in both sums `5 + 6 + 1` and `6 + 1 + 1` in the array `[5,6,1,1,2,3,4]`.

Assume you have computed the sum `5 + 6 + 1 = 12`. To compute the next sum `6 + 1 + 1`, keep the sum `6 + 1` from previous one by subtracting `12 - 5 = 7`. Then add it with the new card's points `7 + 1 = 8`.

The value `k` in this example is not too large to see the effect but I believe you can see how it helps when `k` is very large. 

On the other hand, you do not have to use extra space for the concatenation. You can use the modulo operator `%` on the indices.

### Code
```cpp
#include <iostream>
#include <vector>
using namespace std;
int maxScore(vector<int>& cardPoints, int k) {
    int maxSum = 0;
    int sum = 0;
    // Compute the sum of the last k cards
    for (int i = cardPoints.size() - k; i < cardPoints.size(); i++) {
        sum += cardPoints[i];
    }
    maxSum = max(maxSum, sum);
    // Compute the other sums
    for (int i = cardPoints.size() - k + 1; i <= cardPoints.size(); i++) {
        sum = sum - cardPoints[i - 1] + cardPoints[(i - 1 + k) % cardPoints.size()];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}
int main() {
    vector<int> cardPoints{1,2,3,4,5,6,1};
    cout << maxScore(cardPoints, 3) << endl;
    cardPoints = {2,2,2};
    cout << maxScore(cardPoints, 2) << endl;
    cardPoints = {9,7,7,9,7,7,9};
    cout << maxScore(cardPoints, 7) << endl;
}
```
```plain
Output:
12
4
55
```

### Complexity
* Runtime: `O(k)`.
* Extra space: `O(1)`.

## References
* [https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)
* [https://www.leetsolve.com/1423-maximum-points-you-can-obtain-from-cards](https://www.leetsolve.com/1423-maximum-points-you-can-obtain-from-cards)