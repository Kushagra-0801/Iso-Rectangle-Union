#include <cstdint>
#include <string>

class Point {
   public:
    int32_t x, y;
    Point(int32_t x1, int32_t y1) {
        x = x1;
        y = y1;
    }
};

std::string print_point(const Point &);
