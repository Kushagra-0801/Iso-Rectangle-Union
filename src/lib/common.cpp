#include "common.hpp"

std::array<Edge, 4> Rectangle::into_edges() const {
    return {Edge(y_interval(), upper_left().x, EdgeType::Left),
            Edge(x_interval(), upper_left().y, EdgeType::Top),
            Edge(y_interval(), lower_right().x, EdgeType::Right),
            Edge(x_interval(), lower_right().y, EdgeType::Bottom)};
}

bool Stripe::is_subset_of(const Stripe &s) const {
    auto it1 = this->m_x_union.cbegin();
    auto it1_end = this->m_x_union.cend();
    auto it2 = s.m_x_union.cbegin();
    auto it2_end = s.m_x_union.cend();

    while (it1 != it1_end && it2 != it2_end) {
        if (*it1 == *it2) {
            it1++;it2++;
        } else if (*it1 > *it2) {
            *it2++;
        } else {
            return false;
        }
    }
    return it1 == it1_end;
}

bool Interval::is_subset_of(const Interval& i) const {
    return bot >= i.bot && top <= i.top;
}
