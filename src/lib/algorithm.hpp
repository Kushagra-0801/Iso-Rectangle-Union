#ifndef DAA_ALGO
#define DAA_ALGO

#include <tuple>
#include <vector>

#include "common.hpp"

std::vector<Stripe> rectangle_dac(std::vector<Rectangle>& rects);

std::tuple<std::vector<Interval>, std::vector<Interval>, std::vector<Coord>,
           std::vector<Stripe>>
stripes(std::vector<Edge>& v, Interval x_ext);

#endif