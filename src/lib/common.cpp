#include "common.hpp"

#include <sstream>
#include <string>

std::string print_point(const Point& p) {
    std::stringstream s;
    s << "< " << p.x << ", " << p.y << " >";
    return s.str();
}