#include <iostream>
#include <thread>
#include <semaphore>
#include <functional>
using namespace std;

class FooBar {
private:
    int n;
    binary_semaphore fooSem{1}; // foo goes first
    binary_semaphore barSem{0}; // bar waits

public:
    FooBar(int n) : n(n) {}

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            fooSem.acquire();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            barSem.release();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            barSem.acquire();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            fooSem.release();
        }
    }
};

int main() {
    FooBar fb(5);
    thread t1(&FooBar::foo, &fb, []{ cout << "foo"; });
    thread t2(&FooBar::bar, &fb, []{ cout << "bar"; });
    t1.join();
    t2.join();
    cout << endl;
    return 0;
}