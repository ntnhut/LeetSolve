#include <iostream>
#include <vector>
using namespace std;

//! @return true if all n new flowers can be planted in the empty plots 
//!             and no two flowers are adjacent.
//! @param flowerbed an array of plots indicating if a flower can be planted.
//!                 Values are 0 (empty, available to plant) and 1 (not empty).
//! @param n the number of new flowers to be planted.
//! @author Nhut Nguyen
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n == 0) {
        return true;
    }
    flowerbed.insert(flowerbed.begin(), 0);
    flowerbed.push_back(0);
    int i = 1;
    while (i < flowerbed.size() - 1) {
        if (flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0) {
            flowerbed[i] = 1;
            n--;
            i+=2;
        } else {
            i++;
        }
    }
    return n <= 0;
}

int main() {
    vector<int> flowerbed{1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 1) << endl;
    flowerbed = {1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 2) << endl;
}