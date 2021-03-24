#include <iostream>

#include "lib/algorithm.hpp"
#include "lib/common.hpp"
#include "lib/generator.hpp"

int main() {
    // SetGenerator gen;
    // const auto rects = gen.rects(5);

    std::vector<Rectangle> rects = {
        Rectangle{Point{0, 10}, Point{10, 0}},
        Rectangle{Point{10, 20}, Point{20, 10}},
        Rectangle{Point{20, 10}, Point{30, 0}},
        Rectangle{Point{0, 30}, Point{10, 20}},
        Rectangle{Point{20, 30}, Point{30, 20}},
    };

    for (auto &&r : rects) {
        std::cout << r.upper_left().x << " " << r.upper_left().y << " : "
                  << r.lower_right().x << " " << r.lower_right().y << std::endl;
    }
    auto S = rectangle_dac(rects);
    auto m = measure(S);
    std::cout << "Measure: " << m << std::endl;
    std::cout << "Contour: [";
    auto edges = contour(rects, S);
    for (auto e : edges) {
        std::cout << "{" << e.coord() << ": " << e.interval().bot << ", "
                  << e.interval().top << "}, ";
    }
    std::cout << "]" << std::endl;

    return EXIT_SUCCESS;
}
