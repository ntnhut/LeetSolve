#include <iostream>
#include <vector>
using namespace std;

bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n == 0) {
        return true;
    }
    flowerbed.insert(flowerbed.begin(),0);
    flowerbed.push_back(0);
    int i = 1;
    while (i < flowerbed.size() - 1) {
        if (flowerbed[i-1] + flowerbed[i] + flowerbed[i+1] == 0) {
            flowerbed[i] = 1;
            n--;
            if (n == 0) {
                return true;
            }
        }
        i++;
    }
    return false;
}

int main() {
    vector<int> flowerbed{1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 1) << endl;
    flowerbed = {1,0,0,0,1};
    cout << canPlaceFlowers(flowerbed, 2) << endl;
}