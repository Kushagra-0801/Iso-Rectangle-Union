#include "generator.hpp"

std::vector<Rectangle> SetGenerator::int_rects(size_t n) {
    std::vector<Rectangle> rects;
    rects.reserve(n);
    for (size_t i = 0; i < n; i++) {
        const double ulx = (double)(int)distrib(engine);
        const double lry = (double)(int)distrib(engine);
        const double lrx = (double)(int)distrib(engine) + ulx + 1;
        const double uly = (double)(int)distrib(engine) + lry + 1;
        rects.push_back(Rectangle{Point{ulx, uly}, Point{lrx, lry}});
    }
    return rects;
}

std::vector<Rectangle> SetGenerator::real_rects(size_t n) {
    std::vector<Rectangle> rects;
    rects.reserve(n);
    for (size_t i = 0; i < n; i++) {
        const double ulx = distrib(engine);
        const double lry = distrib(engine);
        const double lrx = distrib(engine) + ulx + 0.0001;
        const double uly = distrib(engine) + lry + 0.0001;
        rects.push_back(Rectangle{Point{ulx, uly}, Point{lrx, lry}});
    }
    return rects;
}
