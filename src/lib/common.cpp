#include "common.hpp"

std::array<Edge, 4> Rectangle::into_edges() const {
    return {Edge(y_interval(), upper_left().x, EdgeType::Left),
            Edge(x_interval(), upper_left().y, EdgeType::Top),
            Edge(y_interval(), lower_right().x, EdgeType::Right),
            Edge(x_interval(), lower_right().y, EdgeType::Bottom)};
}

bool Interval::is_subset_of(const Interval& i) const {
    return bot >= i.bot && top <= i.top;
}
