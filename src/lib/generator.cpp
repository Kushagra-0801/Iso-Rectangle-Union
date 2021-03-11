#include "generator.hpp"

std::vector<Rectangle> SetGenerator::rects(size_t n) {
    std::vector<Rectangle> rects;
    rects.reserve(n);
    for (size_t i = 0; i < n; i++) {
        const auto ulx = distrib(engine);
        const auto lry = distrib(engine);
        const auto lrx = distrib(engine) + ulx + 1;
        const auto uly = distrib(engine) + lry + 1;
        rects.push_back(
            Rectangle{Point<int32_t>{ulx, uly}, Point<int32_t>{lrx, lry}});
    }
    return rects;
}
