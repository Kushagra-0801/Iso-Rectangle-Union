#include <iostream>

#include "lib/common.hpp"

int main() {
    const Point p(1, 5);
    std::cout << "Hello World" << std::endl;
    std::cout << print_point(p) << std::endl;
    return 0;
}
