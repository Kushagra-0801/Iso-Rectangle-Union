#include "algorithm.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

#include "common.hpp"
std::vector<Stripe> rectangle_dac(std::vector<Rectangle>& rects) {
    std::vector<Edge> vertical_edges;
    vertical_edges.reserve(2 * rects.size());
    for (auto&& r : rects) {
        auto [left, _, right, _] = r.into_edges();
        vertical_edges.push_back(left);
        vertical_edges.push_back(right);
    }
    auto [_, _, _, s] = stripes(vertical_edges, {INT32_MIN, INT32_MAX});
    return s;
}

std::tuple<std::vector<Interval>, std::vector<Interval>, std::vector<Coord>,
           std::vector<Stripe>>
stripes(std::vector<Edge>& v, Interval x_ext) {
    if (v.size() == 1) {
        std::vector<Interval> l, r;
        if (v[0].type() == EdgeType::Left) {
            l = {v[0].interval()};
        } else {
            r = {v[0].interval()};
        }
        std::vector<Coord> p{INT32_MIN, v[0].interval().bot,
                             v[0].interval().top, INT32_MAX};
        std::vector<Stripe> S;
        for (auto i : partition(p)) {
            Stripe s{x_ext, i};
            if (i == v[0].interval()) {
                if (v[0].type() == EdgeType::Left) {
                    s.m_x_union = {v[0].coord(), x_ext.top};
                } else {
                    s.m_x_union = {x_ext.bot, v[0].coord()};
                }
            }
            S.push_back(s);
        }
        return {l, r, p, S};
    } else {
        size_t median = v.size() / 2;
        std::nth_element(v.begin(), v.begin() + median, v.end());
        std::vector<Edge> v1{v.begin(), v.begin() + median};
        std::vector<Edge> v2{v.begin() + median, v.end()};
        Coord xm = (v[median].coord() +
                    std::max_element(v1.begin(), v1.end())->coord()) /
                   2;
        auto [l1, r1, p1, s1] = stripes(v1, {x_ext.bot, xm});
        auto [l2, r2, p2, s2] = stripes(v2, {xm, x_ext.top});
        return {l1, r1, p1, s1};
    }
}

std::vector<Interval> partition(std::vector<Coord>& y) {
    sort(y.begin(), y.end());
    std::vector<Interval> res;
    std::adjacent_difference(y.begin(), y.end(), std::back_inserter(res),
                             [](auto a, auto b) { return Interval(a, b); });
    return res;
}
