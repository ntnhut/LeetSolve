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
