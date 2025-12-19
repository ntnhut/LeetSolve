#include <string>
#include <vector>
#include <print>
#include <cassert>
using namespace std;
class Bitset {
    string bits;
    int count_;
    bool isFlipped;

public:
    Bitset(int size) : bits(size, '0'), count_(0), isFlipped(false) {}

    void fix(int idx) {
        // If not flipped, we want '1'. If flipped, we want '0' physically.
        char target = isFlipped ? '0' : '1';
        count_ += (bits[idx] != target);
        bits[idx] = target;
    }

    void unfix(int idx) {
        char target = isFlipped ? '1' : '0';
        count_ -= (bits[idx] != target);
        bits[idx] = target;
    }

    void flip() {
        isFlipped = !isFlipped;
        count_ = bits.size() - count_;
    }

    bool all() {
        return count_ == bits.size();
    }

    bool one() {
        return count_ > 0;
    }

    int count() {
        return count_;
    }

    string toString() {
        if (!isFlipped) return bits;
        
        // Only perform the O(N) conversion when the user asks for the string
        string res = bits;
        for (char &c : res) {
            c = (c == '0' ? '1' : '0');
        }
        return res;
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
