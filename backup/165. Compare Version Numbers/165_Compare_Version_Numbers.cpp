#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

vector<int> toVector(const string& version) {
    vector<int> revisions;
    string revision;
    for (char c : version) {
        if (c != '.') {
            revision += c;
        } else {
            revisions.push_back(stoi(revision));
            revision = "";
        }
    }
    revisions.push_back(stoi(revision));
    return revisions;
}

//! @param version1 a string contains only digits and '.'
//! @param version2 a string contains only digits and '.'
//! @return -1, 1 or 0 if version1 is less than, bigger than or equal to version 2.
//! @author Nhut Nguyen
int compareVersion(string version1, string version2) { 
    vector<int> revisions1 = toVector(version1);    
    vector<int> revisions2 = toVector(version2);

    int i = 0;
    while (i < revisions1.size() && i < revisions2.size()) {
        if (revisions1[i] < revisions2[i]) {
            return -1;
        } else if (revisions1[i] > revisions2[i]) {
            return 1;
        }
        i++;
    }
    int remain1 = accumulate(revisions1.begin() + i, revisions1.end(), 0);
    int remain2 = accumulate(revisions2.begin() + i, revisions2.end(), 0);
    if (remain1 < remain2) {
        return -1;
    } else if (remain1 > remain2) {
        return 1;
    }
    return 0;
}

int main() {
    cout << compareVersion("1.01", "1.001") << endl;
    cout << compareVersion("1.0", "1.0.0") << endl;
    cout << compareVersion("0.1", "1.1") << endl;
}
