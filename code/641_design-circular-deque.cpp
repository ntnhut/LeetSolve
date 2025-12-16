#include <vector>
#include <cassert>
class MyCircularDeque {
    std::vector<int> data_;
    int k_;
    int size_;
    int front_;

public:
    MyCircularDeque(int k) : k_(k), size_(0), front_(0) {
        data_.resize(k_);
    }

    bool insertFront(int value) {
        if (isFull()) return false;
        // Move front backward: (current - 1 + k) % k
        front_ = (front_ - 1 + k_) % k_;
        data_[front_] = value;
        size_++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) return false;
        // Rear is always (front + size) % k before incrementing size        
        data_[(front_ + size_) % k_] = value;
        size_++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) return false;
        front_ = (front_ + 1) % k_;
        size_--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) return false;
        // No need to change front_, just decrement size
        size_--;
        return true;
    }

    int getFront() {
        return isEmpty() ? -1 : data_[front_];
    }

    int getRear() {
        return isEmpty() ? -1 : data_[(front_ + size_ - 1) % k_];
    }

    bool isEmpty() {
        return size_ == 0;
    }

    bool isFull() {
        return size_ == k_;
    }
};

int main() {
    MyCircularDeque d(3);
    assert(d.insertLast(1));
    assert(d.insertLast(2));
    assert(d.insertFront(3));
    assert(d.isFull());
    assert(!d.insertFront(4));
    assert(d.getRear() == 2);
    assert(d.isFull());
    assert(d.deleteLast());
    assert(d.insertFront(4));
    assert(d.getFront() == 4);
    return 0;
}

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */