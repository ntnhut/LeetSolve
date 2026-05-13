#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class FooBar {
private:
  int n;
  bool fooTurn = true;
  mutex m;
  condition_variable cv;

public:
  FooBar(int n) : n(n) {}

  void foo(function<void()> printFoo) {
    for (int i = 0; i < n; i++) {
      {
        unique_lock<mutex> l(m);
        cv.wait(l, [this]{ return fooTurn; });
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        fooTurn = false;
      }
      cv.notify_one();
    }
  }

  void bar(function<void()> printBar) {
    for (int i = 0; i < n; i++) {
      {
        unique_lock<mutex> l(m);
        cv.wait(l, [this]{ return !fooTurn; });
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        fooTurn = true;
      }
      cv.notify_one();
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