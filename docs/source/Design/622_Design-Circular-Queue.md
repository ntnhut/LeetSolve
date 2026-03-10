Solution 1
```cpp
class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        v_.resize(k);
        front_ = 0;
        rear_ = -1;
        size_ = 0;
    }
    // Inserts an element into the circular queue. 
    // Return true if the operation is successful.
    bool enQueue(int value) {
        if (isFull()) return false;
        rear_ = (rear_ + 1) % v_.size();
        v_[rear_] = value;
        size_++;
        return true;
    }
    // Deletes an element from the circular queue. Return true if the operation is successful.
    bool deQueue() {
        if (isEmpty()) return false;
        front_ = (front_ + 1) % v_.size();
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
    int rear_;
    int front_;
    int size_;
};

```
