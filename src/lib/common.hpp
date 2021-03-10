#ifndef DAA_COMMON
#define DAA_COMMON
#include <string>

class Point {
   public:
    double x, y;
    Point(double x1, double y1) {
        x = x1;
        y = y1;
    }
};

struct Rectangle {
    Point upper_left;
    Point lower_right;
};

std::string print_point(const Point &);
#endif
