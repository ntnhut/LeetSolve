#include <vector>
#include <iostream>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> answer(temperatures.size(), 0);
    for (int i = temperatures.size() - 2; i >= 0 ; i--) {
        int j = i + 1;
        while (j < temperatures.size() && temperatures[j] <= temperatures[i]) {
            if (answer[j] > 0) { // there is some temperature bigger than temperatures[j]
                j += answer[j];  // go to that value 
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
