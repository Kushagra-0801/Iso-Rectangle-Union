#ifndef DAA_COMMON
#define DAA_COMMON

#include <string>

template <typename T>
class Point {
   public:
    T x, y;
    Point(T x1, T y1) {
        x = x1;
        y = y1;
    }
};

struct Rectangle {
    Point<int32_t> upper_left;
    Point<int32_t> lower_right;
};

#endif
