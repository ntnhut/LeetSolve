#include <cassert>
#include <vector>
class MyCircularQueue {
public:
    MyCircularQueue(int k) : v_(k), front_(0), rear_(-1), size_(0) {
    }
    // Inserts an element into the circular queue. 
    // Return true if the operation is successful.
    bool enQueue(int value) {
        if (isFull()) return false;
        rear_++;
        if (rear_ == v_.size()) rear_ = 0;
        v_[rear_] = value;
        size_++;
        return true;
    }
    // Deletes an element from the circular queue. Return true if the operation is successful.
    bool deQueue() {
        if (isEmpty()) return false;
        front_++;
        if (front_ == v_.size()) front_ = 0;
        size_--;
        return true;
    }

    //! Gets the front item from the queue. If the queue is empty, return -1.
    int Front() {
        if (isEmpty()) return -1;
        return v_[front_];
    }
    //! Gets the last item from the queue. If the queue is empty, return -1.
    int Rear() {
        if (isEmpty()) return -1;
        return v_[rear_];
    }
    // Checks whether the circular queue is empty or not.
    bool isEmpty() {
        return size_ == 0;
    }
    // Checks whether the circular queue is full or not.
    bool isFull() {
        return size_ == v_.size();
    }
private:
    std::vector<int> v_;
    size_t rear_;
    size_t front_;
    size_t size_;
};

int main()
{
    MyCircularQueue q(3);
    assert(q.enQueue(1) == true);
    assert(q.enQueue(2) == true);
    assert(q.enQueue(3) == true);
    assert(q.enQueue(4) == false);
    assert(q.Rear() == 3);
    assert(q.isFull() == true);
    assert(q.deQueue() == true);
    assert(q.enQueue(4) == true);
    assert(q.Rear() == 4);
}
