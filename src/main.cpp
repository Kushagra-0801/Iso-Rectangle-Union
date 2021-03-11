#include <iostream>

#include "lib/common.hpp"
#include "lib/generator.hpp"

int main() {
    std::cout << "Hello World" << std::endl;

    SetGenerator gen;
    const auto rects = gen.rects(5);
    for (auto &&r : rects) {
        std::cout << r.upper_left.x << " " << r.upper_left.y << " : "
                  << r.lower_right.x << " " << r.lower_right.y << std::endl;
    }
    return EXIT_SUCCESS;
}
