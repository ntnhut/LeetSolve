#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> result;    
    unordered_map<char,char> w_to_p, p_to_w; // need two maps for the bijection
    int i;
    for (string& w : words) {
        w_to_p.clear();
        p_to_w.clear();
        i = 0;
        while (i < w.length()) {
            if (w_to_p.find(w[i]) != w_to_p.end()) {
                // w[i] was mapped to some letter x, but x != pattern[i]
                if (w_to_p[w[i]] != pattern[i]) {
                    break;
                }
            } else {
                if (p_to_w.find(pattern[i]) != p_to_w.end()) {
                    // w[i] was not mapped yet but pattern[i] was already mapped to some letter
                    break;
                }
                // build the bijection w[i] <-> pattern[i]
                w_to_p[w[i]] = pattern[i];
                p_to_w[pattern[i]] = w[i];
            }
            i++;
        }
        if (i == w.length()) {
            result.push_back(w);
        }
    }
    return result;
}

void printResult(const vector<string>& result) {
    cout << "[";
    for (const string& s : result) {
        cout << s << ",";
    }
    cout << "]\n";
}
int main() {
    vector<string> words{"abc","deq","mee","aqq","dkd","ccc"};
    auto result = findAndReplacePattern(words, "abb");
    printResult(result);
    words = {"a", "b", "c"};
    result = findAndReplacePattern(words, "abb");
    printResult(result);
}