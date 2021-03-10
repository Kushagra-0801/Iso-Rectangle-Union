#include <iostream>

#include "lib/common.hpp"
#include "lib/generator.hpp"

int main() {
    const Point p(1, 5);
    std::cout << "Hello World" << std::endl;
    std::cout << print_point(p) << std::endl;

    SetGenerator gen;
    const auto rects = gen.real_rects(5);
    for (auto &&r : rects) {
        std::cout << r.lower_left.x << " " << r.lower_left.y << " : "
                  << r.upper_right.x << " " << r.upper_right.y << std::endl;
    }
    return EXIT_SUCCESS;
}
