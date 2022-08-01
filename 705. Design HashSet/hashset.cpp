#include <iostream>
#include <vector>
using namespace std;

class MyHashSet {
    vector<bool> _v;
public:
    MyHashSet() : _v(1000001, false){        
    }   
    void add(int key) {
        _v[key] = true;
    }    
    void remove(int key) {
        _v[key] = false;
    }    
    bool contains(int key) {
        return _v[key];
    }
};

int main() {
    MyHashSet m;
    m.add(1);
    m.add(2);
    cout << m.contains(1) << endl;
    cout << m.contains(3) << endl;
    m.add(2);
    cout << m.contains(2) << endl;
    m.remove(2);
    cout << m.contains(2) << endl;
}