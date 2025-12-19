#include <string>
#include <vector>
#include <print>
#include <cassert>
using namespace std;
class Bitset {
    string bits;
    int count_;
public:
    Bitset(int size) : bits(size, '0'), count_(0) {        
    }
    
    void fix(int idx) {
        count_ += (bits[idx] == '0');
        bits[idx] = '1';        
    }
    
    void unfix(int idx) {
        count_ -= (bits[idx] == '1');
        bits[idx] = '0';        
    }
    
    void flip() {
        for (auto& c : bits) {
            c ^= 1;
        }
        count_ = bits.size() - count_;
    }
    
    bool all() {
        return count_ == bits.size();
    }
    
    bool one() {
        return count_ >= 1;
    }
    
    int count() {
        return count_;
    }
    
    string& toString() {
        return bits;
    }
};

int main() {
    Bitset bs(5);
    assert(bs.toString() == "00000");
    bs.fix(3);
    bs.fix(1);
    bs.flip();
    assert(bs.all() == false);
    bs.unfix(0);
    bs.flip();
    assert(bs.one() == true);
    bs.unfix(0);
    assert(bs.count() == 2);
    assert(bs.toString() == "01010");
    return 0;
}
