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
vector<int> dailyTemperatures(vector<int>& temperatures) 
{
    vector<int> answer(temperatures.size());
    for (int i = 0; i < temperatures.size(); i++) 
    {
        answer[i] = 0;
        for (int j = i + 1; j < temperatures.size(); j++) 
        {
            if (temperatures[j] > temperatures[i]) 
            {
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

### Code explanation

1. The code initializes the `answer` vector with the same size as the `temperatures` vector, with all elements initially set to 0. This vector will store the number of days you need to wait for a warmer temperature for each day.

2. The outer loop iterates through the `temperatures` vector, with `i` representing the current day for which you want to find the waiting period.

3. Initially, the number of days to wait is set to 0 for the current day `i`. This is the default value in case there are no warmer days ahead.

4. The inner loop iterates from the next day `i + 1` until the end of the `temperatures` vector. It is used to find a warmer day.

5. A condition checks if the temperature on day `j` is higher than the temperature on day `i`. If this condition is met, it means you've found a warmer day.

6. If a warmer day is found, the code calculates the number of days you need to wait by subtracting the current day `i` from the warmer day `j`. This value is then assigned to `answer[i]`.

7. After finding a warmer day, the inner loop is exited because there's no need to continue searching for warmer days for the same day `i`. We move on to the next day in the outer loop.

8. Finally, the `answer` vector is returned, which contains the number of days to wait for a warmer temperature for each day in the `temperatures` vector.


### Complexity
This solution uses two nested loops to compare each day's temperature with the temperatures of the subsequent days to find the next warmer day. It calculates and stores the waiting period in the `answer` vector and returns it as the result. 

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
vector<int> dailyTemperatures(vector<int>& temperatures) 
{
    vector<int> answer(temperatures.size(), 0);
    for (int i = temperatures.size() - 2; i >= 0 ; i--) 
    {
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

1. The outer loop iterates backward through the `temperatures` vector, starting from the second-to-last day and moving backwards the first day. This is because you can't find a warmer day after the last day, so there's no need to check it.

2. Starting from `j = i + 1`, the inner loop iterates as long as `j` is within the bounds of the `temperatures` vector and the temperature on day `j` is less than or equal to the temperature on the current day `i`. This loop efficiently finds the next warmer day.

3. If there is a non-zero value in the `answer` vector at position `j`, it means there's already a known waiting period for that day. In this case, the code skips ahead in the `temperatures` vector by the number of days stored in `answer[j]`. This is an optimization to avoid redundant checks and improve efficiency.
   
4. If there is no known waiting period for day `j`, it means there are no warmer days ahead. In this case, we set `j` to the end of the vector to exit the loop.

5. After finding a warmer day, the code calculates the number of days you need to wait by subtracting the current day `i` from the warmer day `j`. This value is then assigned to `answer[i]`.

6. Finally, the `answer` vector is returned, which contains the number of days to wait for a warmer temperature for each day in the `temperatures` vector.

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
