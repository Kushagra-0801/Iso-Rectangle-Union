#include "generator.hpp"

std::vector<Rectangle> SetGenerator::int_rects(size_t n) {
    std::vector<Rectangle> rects;
    rects.reserve(n);
    for (size_t i = 0; i < n; i++) {
        const double llx = (double)(int)distrib(engine);
        const double lly = (double)(int)distrib(engine);
        const double urx = (double)(int)distrib(engine) + llx + 1;
        const double ury = (double)(int)distrib(engine) + lly + 1;
        rects.push_back(Rectangle{Point{llx, lly}, Point{urx, ury}});
    }
    return rects;
}

std::vector<Rectangle> SetGenerator::real_rects(size_t n) {
    std::vector<Rectangle> rects;
    rects.reserve(n);
    for (size_t i = 0; i < n; i++) {
        const double llx = distrib(engine);
        const double lly = distrib(engine);
        const double urx = distrib(engine) + llx + 0.0001;
        const double ury = distrib(engine) + lly + 0.0001;
        rects.push_back(Rectangle{Point{llx, lly}, Point{urx, ury}});
    }
    return rects;
}
