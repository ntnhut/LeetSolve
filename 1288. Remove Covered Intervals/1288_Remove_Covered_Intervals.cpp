#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//! @param intervals a list of intervals [left_i, right_i]
//! @return the number of remaining intervals after removing all intervals
//!         that are covered by another one in the list
//! @author Nhut Nguyen
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    int count = 0;
    int maxRight = -1;
    int preLeft = -1;
    for (auto& i : intervals) {
        if (i[1] <= maxRight) { // i is covered by some previous interval
            count++;
        } else if (i[0] == preLeft) { // i covers its exact previous one
            count++;
        } else {
            preLeft = i[0];
        }
        maxRight = max(maxRight, i[1]);
    }
    return intervals.size() - count;
}
int main() {
    vector<vector<int>> intervals{{1,4},{3,6},{2,8}};
    cout << removeCoveredIntervals(intervals) << endl; // 2
    intervals = {{1,4},{2,3}};
    cout << removeCoveredIntervals(intervals) << endl; // 1
}
