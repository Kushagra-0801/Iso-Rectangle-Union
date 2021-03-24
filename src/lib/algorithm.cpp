#include "algorithm.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

#include "common.hpp"

std::vector<Interval> partition(std::vector<Coord> &y) {
    std::vector<Interval> res;
    for (size_t i = 1; i < y.size(); i++) {
        res.push_back({y[i - 1], y[i]});
    }
    return res;
}

std::vector<Stripe> copy(std::vector<Stripe> &S, std::vector<Coord> &P,
                         Interval x_int) {
    std::vector<Stripe> S_dash;
    for (auto i : partition(P)) {
        Stripe s_dash{x_int, i};
        for (auto &s : S) {
            if (s_dash.m_y_interval.is_subset_of(s.m_y_interval)) {
                s_dash.x_measure = s.x_measure;
                s_dash.tree = s.tree;
            }
        }
        S_dash.push_back(s_dash);
    }
    return S_dash;
}

void blacken(std::vector<Stripe> &S, std::vector<Interval> &J) {
    for (auto &s : S) {
        for (auto i : J) {
            if (s.m_y_interval.is_subset_of(i)) {
                s.x_measure = s.m_x_interval.top - s.m_x_interval.bot;
                s.tree = nullptr;
            }
        }
    }
}

std::vector<Stripe> concat(std::vector<Stripe> &S1, std::vector<Stripe> &S2,
                           std::vector<Coord> &P, Interval x_int) {
    std::vector<Stripe> S;
    for (auto i : partition(P)) {
        Stripe s{x_int, i};
        bool flag = false;
        for (auto s1 : S1) {
            if (s1.m_y_interval == s.m_y_interval) {
                for (auto s2 : S2) {
                    if (s2.m_y_interval == s.m_y_interval) {
                        s.x_measure = s1.x_measure + s2.x_measure;
                        if (s1.tree && s2.tree) {
                            s.tree = new Ctree{s1.m_x_interval.top, Lru::Undef,
                                               s1.tree, s2.tree};
                        } else if (s1.tree) {
                            s.tree = s1.tree;
                        } else if (s2.tree) {
                            s.tree = s2.tree;
                        } else {
                            s.tree = nullptr;
                        }
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) {
                break;
            }
        }
        S.push_back(s);
    }
    return S;
}

std::vector<Stripe> rectangle_dac(std::vector<Rectangle> &rects) {
    std::vector<Edge> vertical_edges;
    vertical_edges.reserve(2 * rects.size());
    for (auto &r : rects) {
        auto [left, top, right, bottom] = r.into_edges();
        vertical_edges.push_back(left);
        vertical_edges.push_back(right);
    }
    auto [l, r, p, s] = stripes(vertical_edges, {INT32_MIN, INT32_MAX});
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
                    s.x_measure = x_ext.top - v[0].coord();
                    s.tree = new Ctree{v[0].coord(), Lru::Left};
                } else {
                    s.x_measure = v[0].coord() - x_ext.bot;
                    s.tree = new Ctree{v[0].coord(), Lru::Right};
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
        std::set_union(l_temp.cbegin(), l_temp.cend(), l2.cbegin(), l2.cend(),
                       std::back_inserter(l));

        // r = r1 U (r2 - lr);
        std::set_difference(r2.cbegin(), r2.cend(), lr.cbegin(), lr.cend(),
                            std::back_inserter(r_temp));
        std::set_union(r1.cbegin(), r1.cend(), r_temp.cbegin(), r_temp.cend(),
                       std::back_inserter(r));

        // p = p1 U p2
        std::set_union(p1.cbegin(), p1.cend(), p2.cbegin(), p2.cend(),
                       std::back_inserter(p));

        auto S_left = copy(s1, p, {x_ext.bot, xm});
        auto S_right = copy(s2, p, {xm, x_ext.top});

        blacken(S_left, r_temp);
        blacken(S_right, l_temp);

        S = concat(S_left, S_right, p, x_ext);

        return {l, r, p, S};
    }
}

Coord measure(std::vector<Stripe> &S) {
    Coord res = 0;
    for (auto &s : S) {
        res += s.x_measure * (s.m_y_interval.top - s.m_y_interval.bot);
    }
    return res;
}

void dfs(Ctree *tree, std::vector<Ctree> &leaves) {
    if (tree->side == Lru::Undef) {
        dfs(tree->lson, leaves);
        dfs(tree->rson, leaves);
    } else {
        leaves.push_back(*tree);
    }
}

void contour_pieces(std::vector<Edge> &parts, Edge h, Stripe &s) {
    std::vector<Ctree> leaves;
    if (s.tree) {
        dfs(s.tree, leaves);
    }
    if (leaves.empty()) {
        parts.push_back(h);
    } else {
        auto iter = leaves.cbegin();
        if (iter->side == Lru::Left && h.interval().bot < iter->x) {
            parts.push_back({{h.interval().bot, iter->x}, h.coord(), h.type()});
        }
        iter++;
        while (iter != leaves.cend()) {
            if (auto prev = iter - 1;
                prev->side == Lru::Right && iter->side == Lru::Left) {
                parts.push_back({{prev->x, iter->x}, h.coord(), h.type()});
            }
            iter++;
        }
        iter--;
        if (iter->side == Lru::Right && h.interval().top > iter->x) {
            parts.push_back({{iter->x, h.interval().top}, h.coord(), h.type()});
        }
    }
}

std::vector<Edge> contour(std::vector<Rectangle> &rects,
                          std::vector<Stripe> &S) {
    std::vector<Edge> contour_parts;
    for (auto &&r : rects) {
        auto [left, top, right, bottom] = r.into_edges();
        for (auto &s : S) {
            if (s.m_y_interval.bot == top.coord()) {
                contour_pieces(contour_parts, top, s);
            } else if (s.m_y_interval.top == bottom.coord()) {
                contour_pieces(contour_parts, bottom, s);
            }
        }
    }
    return contour_parts;
}
