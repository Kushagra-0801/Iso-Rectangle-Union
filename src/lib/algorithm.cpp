#include "algorithm.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

#include "common.hpp"
std::vector<Stripe> rectangle_dac(std::vector<Rectangle> &rects) {
    std::vector<Edge> vertical_edges;
    vertical_edges.reserve(2 * rects.size());
    for (auto &&r : rects) {
        auto [left, _, right, _] = r.into_edges();
        vertical_edges.push_back(left);
        vertical_edges.push_back(right);
    }
    auto [_, _, _, s] = stripes(vertical_edges, {INT32_MIN, INT32_MAX});
    return s;
}

std::tuple<std::vector<Interval>, std::vector<Interval>, std::vector<Coord>,
           std::vector<Stripe>>
stripes(std::vector<Edge> &v, Interval x_ext) {
    std::vector<Interval> l, r;
    std::vector<Coord> p;
    std::vector<Stripe> S;
    if (v.size() == 1) {
        if (v[0].type() == EdgeType::Left) {
            l = {v[0].interval()};
        } else {
            r = {v[0].interval()};
        }
        p = {INT32_MIN, v[0].interval().bot, v[0].interval().top, INT32_MAX};
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
        std::vector<Interval> lr;
        std::set_intersection(l1.cbegin(), l1.cend(), r2.cbegin(), r2.cend(),
                              std::back_inserter(lr));
        std::vector<Interval> l_temp, r_temp;

        // l = (l1 - lr) U l2;
        std::set_difference(l1.cbegin(), l1.cend(), lr.cbegin(), lr.cend(),
                            std::back_inserter(l_temp));
        std::set_union(l_temp.begin(), l_temp.end(), l2.begin(), l2.end(),
                       std::back_inserter(l));

        // r = r1 U (r2 - lr);
        std::set_difference(r2.cbegin(), r2.cend(), lr.cbegin(), lr.cend(),
                            std::back_inserter(r_temp));
        std::set_union(r1.cbegin(), r1.cend(), r_temp.cbegin(), r_temp.cend(),
                       std::back_inserter(r));

        // p = p1 U p2
        std::set_union(p1.cbegin(), p1.cend(), p2.cbegin(), p2.cend(),
                       std::back_inserter(p));

        auto S_left = copy(s1, p, {x_int.bot, x_m});
        auto S_right = copy(s2, p, {x_m, x_int.top});

        blacken(s_left, r_temp);
        blacken(S_right, l_temp);

        return {l, r, p, S};
    }
}

std::vector<Interval> partition(std::vector<Coord> &y) {
    sort(y.begin(), y.end());
    std::vector<Interval> res;
    std::adjacent_difference(y.begin(), y.end(), std::back_inserter(res),
                             [](auto a, auto b) { return Interval(a, b); });
    return res;
}

std::vector<Stripe> copy(std::vector<Stripe> &S, std::vector<Coord> &P,
                         Interval x_int) {
    std::vector<Stripe> S_dash;
    for (auto i : partition(p)) {
        Stripe s_dash{x_int, i};
        for (auto &s : S) {
            if (s_dash.is_subset_of(s)) {
                s_dash.m_x_union = s.m_x_union;
            }
        }
        S_dash.push_back(s_dash);
    }
}

void blacken(std::vector<Stripe> &S, std::vector<Interval> &J) {
    for (auto &s : S) {
        for (auto i : J) {
            if (s.m_y_interval.is_subset_of(i)) {
                s.m_x_union = {s.m_x_interval};
            }
        }
    }
}

std::vector<Stripe> concat(std::vector<Stripe> &S1, std::vector<Stripe> &S2,
                           std::vector<Coord> &P, Interval x_int) {
    std::vector<Stripe> S;
    for (auto i : partition(P)) {
        Stripe s{x_int, i};
    OUTER:
        for (auto s1 : S1) {
            if (s1.m_y_interval == s.m_y_interval) {
                for (auto s2 : S2) {
                    if (s2.m_y_interval == s.m_y_interval) {
                        s.m_x_union = concat_helper(s1.m_x_union, s2.m_x_union);
                        break OUTER;
                    }
                }
            }
        }
        S.push_back(s);
    }
    return S;
}

std::vector<Interval> concat_helper(std::vector<Interval> &s1,
                                    std::vector<Interval> &s2) {
    auto is_adjacent = [](auto i, auto j) {
        return j.top == i.bot || j.bot == i.top;
    };
    auto merge = [](auto i, auto j) {
        if (j.top == i.bot) {
            return {j.bot, i.top};
        } else {
            return {i.bot, j.top};
        }
    };

    std::vector<Interval> S;
    auto it1 = s1.cbegin();
    auto it1_end = s1.cend();
    auto it2 = s2.cbegin();
    auto it2_end = s2.cend();
    while (it1 != it1_end && it2 != it2_end) {
        if (is_adjacent(*it1, *it2)) {
            S.push_back(merge(*it1, *it2));
            it1++;
            it2++;
        } else if (*it1 < *it2) {
            S.push_back(*it1);
            it1++;
        } else {
            S.push_back(*it2);
            it2++;
        }
    }
    while (it1 != it1_end) {
        S.push_back(*it1);
        it1++;
    }
    while (it2 != it2_end) {
        S.push_back(*it2);
        it2++;
    }
    return S;
}