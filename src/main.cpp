#include <iostream>

#include "lib/algorithm.hpp"
#include "lib/common.hpp"
#include "lib/generator.hpp"

int main() {
    // SetGenerator gen;
    // const auto rects = gen.rects(5);

    std::vector<Rectangle> rects = {
        Rectangle{Point{0, 100}, Point{10, 0}},
        Rectangle{Point{10, 200}, Point{20, 100}},
        Rectangle{Point{20, 100}, Point{30, 0}},
        Rectangle{Point{0, 300}, Point{10, 200}},
        Rectangle{Point{20, 300}, Point{30, 200}},
    };
    auto S = rectangle_dac(rects);
    auto m = measure(S);
    std::cout << "Measure: " << m << std::endl;
    std::cout << "Contour: [";
    auto hori_edges = contour(rects, S);
    for (auto e : hori_edges) {
        std::cout << "{" << e.coord() << ": " << e.interval().bot << ", "
                  << e.interval().top << "}, ";
    }
    std::cout << "]" << std::endl;

    for (auto &r : rects) {
        r = Rectangle{r.y_interval(), r.x_interval()};
    }
    S = rectangle_dac(rects);
    std::cout << "YOLO" << std::endl;
    auto verti_edges = contour(rects, S);

    std::cout << "Contour: [";
    for (auto e : verti_edges) {
        std::cout << "{" << e.coord() << ": " << e.interval().bot << ", "
                  << e.interval().top << "}, ";
    }
    std::cout << "]" << std::endl;

    return EXIT_SUCCESS;
}
