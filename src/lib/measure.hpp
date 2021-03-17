#include <vector>

#include "common.hpp"

class MeasureStripe {
   public:
    Interval x_interval;
    Interval y_interval;
    Coord measure;
};

Coord measure(const std::vector<Stripe> &S) {
    Coord ans = 0;
    for (const auto &s : S) {
        ans += measure(s.m_x_union) * (s.m_y_interval.top - s.m_y_interval.bot);
    }
    return ans;
}