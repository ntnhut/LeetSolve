#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//! @return the maximum total number of units that can be put on the truck
//! @param truckSize maximum number of boxes can be put on the truck
//! @param boxTypes an array of boxTypes[i] = {numberOfBoxes_i, numberOfUnitsPerBox_i}.
//! @author Nhut Nguyen
int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    // sort for the boxes based on their number of units
    sort(boxTypes.begin(), boxTypes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] > b[1];
    });
    int maxUnits = 0;
    int i = 0;
    while (truckSize > 0 && i < boxTypes.size()) {
        if (boxTypes[i][0] <= truckSize) {
            maxUnits += boxTypes[i][0] * boxTypes[i][1];
            truckSize -= boxTypes[i][0];
        } else {
            maxUnits += truckSize * boxTypes[i][1];
            break;
        }
        i++;
    }
    return maxUnits;
}
int main() {
    vector<vector<int>> boxTypes{{1,3},{2,2},{3,1}};
    cout << maximumUnits(boxTypes, 4) << endl;
    boxTypes = {{5,10},{2,5},{4,7},{3,9}};
    cout << maximumUnits(boxTypes, 10) << endl;
}