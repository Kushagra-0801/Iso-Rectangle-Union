#ifndef DAA_COMMON
#define DAA_COMMON

#include <array>
#include <string>

typedef int32_t Coord;

class Point {
   public:
    Coord x, y;
    Point(Coord x, Coord y) : x(x), y(y) {}
};

class Interval {
   public:
    Coord bot, top;
    Interval(Coord bot, Coord top) : bot(bot), top(top) {}
};

enum class EdgeType { Left, Top, Right, Bottom };

class Edge {
    Interval m_interval;
    Coord m_coord;
    EdgeType m_type;

   public:
    Edge(Interval i, Coord c, EdgeType t)
        : m_interval(i), m_coord(c), m_type(t) {}
    Interval interval() const { return m_interval; }
    Coord coord() const { return m_coord; }
    EdgeType type() const { return m_type; }
};

class Rectangle {
    Point m_upper_left;
    Point m_lower_right;

   public:
    Rectangle(Point ul, Point lr) : m_upper_left(ul), m_lower_right(lr) {}
    Rectangle(Interval x_axis, Interval y_axis)
        : m_upper_left({x_axis.bot, y_axis.top}),
          m_lower_right({x_axis.top, y_axis.bot}) {}
    Point upper_left() const { return m_upper_left; }
    Point lower_right() const { return m_lower_right; }
    Interval x_interval() const { return {m_upper_left.x, m_lower_right.x}; }
    Interval y_interval() const { return {m_lower_right.y, m_upper_left.y}; }
    std::array<Edge, 4> into_edges() const;
};

#endif
