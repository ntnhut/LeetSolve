#include <set>
#include <iostream>
int main() {
    std::multiset<int> s;
    s.insert(10);
    auto it = s.begin();
    std::cout << *it << std::endl;
    s.insert(50);
    it++;
    std::cout << *it << std::endl;
    s.insert(30);
    std::cout << *it << std::endl;
    s.insert(40);
    it++;
    std::cout << *it << std::endl;
    s.insert(20);
    std::cout << *it << std::endl;

    return 0;
}