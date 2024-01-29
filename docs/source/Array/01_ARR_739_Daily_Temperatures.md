# Daily Temperatures

## [Problem statement](https://leetcode.com/problems/daily-temperatures/)

You are given an array of integers `temperatures`, which represents the daily temperatures. Your task is to create an array `answer` such that `answer[i]` represents the number of days you need to wait after the i-th day to experience a warmer temperature. If there is no future day with a warmer temperature, then `answer[i]` should be set to `0`. 

### Example 1
```text
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

### Example 2
```text
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

### Example 3
```text
Input: temperatures = [30,60,90]
Output: [1,1,0]
```
 
### Constraints
* `1 <= temperatures.length <= 10^5`.
* `30 <= temperatures[i] <= 100`.

## Solution 1: Starting from the first day

For each `temperatures[i]`, find the closest `temperatures[j]` with `j > i` such that `temperatures[j] > temperatures[i]`, then `answer[i] = j - i`. If not found, `answer[i] = 0`.

### Example 1
For `temperatures = [73,74,75,71,69,72,76,73]`:

* `answer[0] = 1` since the next day is warmer (`74 > 73`).
* `answer[1] = 1` since the next day is warmer (`75 > 74`).
* `answer[2] = 4` since only after `4` days it is warmer (`76 > 75`).
* And so on.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> answer(temperatures.size());
    for (int i = 0; i < temperatures.size(); i++) {
        answer[i] = 0;
        for (int j = i + 1; j < temperatures.size(); j++) {
            if (temperatures[j] > temperatures[i]) {
                answer[i] = j - i;
                break;
            }
        }
    }
    return answer;
}
void print(vector<int>& answer) {
    cout << "[";
    for (auto& v : answer ) {
        cout << v << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> temperatures{73,74,75,71,69,72,76,73};
    auto answer = dailyTemperatures(temperatures);
    print(answer);
    temperatures = {30,40,50,60};
    answer = dailyTemperatures(temperatures);
    print(answer);
    temperatures = {30,60,90};
    answer = dailyTemperatures(temperatures);
    print(answer);
}
```
```text
Output:
[1,1,4,2,1,1,0,0,]
[1,1,1,0,]
[1,1,0,]
```

### Code insight

This solution iterates through the temperatures array and, for each temperature, iterates through the remaining temperatures to find the next higher temperature. Storing the time difference between the current day and the next higher temperature day constructs the resulting array representing the number of days until warmer temperatures.

### Complexity

* Runtime: `O(N^2)`, where `N = temperatures.length`.
* Extra space: `O(1)`.

## Solution 2: Starting from the last day

The straightforward solution above is easy to understand, but the complexity is `O(N^2)`. 

The way starting from the first day to the last day does not make use of the knowledge of the `answer[i]` values. 

* The value `answer[i] > 0` tells you that `temperatures[i + answer[i]]` is the next temperature that is warmer than `temperatures[i]`. 
* The value `answer[i] = 0` tells you that there is no warmer temperature than `temperatures[i]`. 

When computing `answer[i]` in the reversed order, you can use that knowledge more efficiently.

Suppose you already know the future values `answer[j]`. To compute an older value `answer[i]` with `i < j`, you need only to compare `temperatures[i]` with `temperatures[i + 1]` and its **chain** of warmer temperatures.  

### Example 1
For `temperatures = [73,74,75,71,69,72,76,73]`. 

Suppose you have computed all `answer[j]` with `j > 2`, `answer = [?,?,?,2,1,1,0,0]`.  

To compute `answer[i = 2]` for `temperatures[2] = 75`, you need to compare it with

* `temperatures[3] = 71 (< 75)`. Go to the next warmer temperature than `temperatures[3]`, which is `temperatures[3 + answer[3]] = temperatures[3 + 2]`. 
* `temperatures[5] = 72 (< 75)`. Go to the next warmer temperature than `temperatures[5]`, which is `temperatures[5 + answer[5]] = temperatures[5 + 1]`. 
* `temperatures[6] = 76 (> 75)`. Stop.
* `answer[i = 2] = j - i = 6 - 2 = 4`.

### Code
```cpp
#include <vector>
#include <iostream>
using namespace std;
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> answer(temperatures.size(), 0);
    for (int i = temperatures.size() - 2; i >= 0 ; i--) {
        int j = i + 1;
        while (j < temperatures.size() && 
               temperatures[j] <= temperatures[i]) {
            // some temperature is bigger than temperatures[j], 
            // go to that value 
            if (answer[j] > 0) { 
                j += answer[j];
            } else {
                j = temperatures.size();    
            }
        }
        if (j < temperatures.size()) {
            answer[i] = j - i;
        }
    }
    return answer;
}
void print(vector<int>& answer) {
    cout << "[";
    for (auto& v : answer ) {
        cout << v << ",";
    }
    cout << "]\n";
}
int main() {
    vector<int> temperatures{73,74,75,71,69,72,76,73};
    auto answer = dailyTemperatures(temperatures);
    print(answer);
    temperatures = {30,40,50,60};
    answer = dailyTemperatures(temperatures);
    print(answer);
    temperatures = {30,60,90};
    answer = dailyTemperatures(temperatures);
    print(answer);
}
```
```text
Output:
[1,1,4,2,1,1,0,0,]
[1,1,1,0,]
[1,1,0,]
```

### Code explanation

The key to this solution lies in its optimized approach to finding the next higher temperature. It utilizes a `while` loop to traverse the `temperatures` array efficiently, skipping elements if they are not potential candidates for a higher temperature. Updating the index based on previously calculated values stored in the `answer` array avoids unnecessary iterations, resulting in improved performance compared to the straightforward nested loop approach.

This improved solution reduces the time complexity to `O(N)` as it iterates through the `temperatures` vector only once, resulting in a more efficient algorithm for finding the waiting periods for each day.

### Complexity
Worse cases for the `while` loop are when most `temperatures[j]` in their chain are cooler than `temperatures[i]`. 

In these cases, the resulting `answer[i]` will be either `0` or a big value `j - i`. Those extreme values give you a huge knowledge when computing `answer[i]` for other older days `i`.

The value `0` would help the `while` loop terminates very soon. On the other hand, the big value `j - i` would help the `while` loop skips the days `j` very quickly.

* Runtime: `O(N)`, where `N = temperatures.length`. 
* Extra space: `O(1)`.


## Tips

In some computations, you could improve the performance by using the knowledge of the results you have computed. 

In this particular problem, it can be achieved by doing it in the reversed order.
