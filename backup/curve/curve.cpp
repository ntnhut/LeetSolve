#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
struct PowerPoint {
    double x;
    double y;
};
struct PowerCurve {
    std::vector<PowerPoint> series;
};
struct FC {
    std::unordered_map<std::string, PowerCurve> init_curve;
    void doSomething() {
        std::cout << "doing..\n";
    }
};
int main() {
    FC fc;
    fc.doSomething();
    std::cout << "well\n";
}