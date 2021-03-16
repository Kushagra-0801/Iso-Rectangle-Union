#ifndef DAA_COMMON
#define DAA_COMMON

#include <array>
#include <set>
#include <string>

typedef int32_t Coord;

class Point {
   public:
    Coord x, y;
    Point() = delete;
    Point(Coord x, Coord y) : x(x), y(y) {}
};

class Interval {
   public:
    Coord bot, top;
    Interval() = delete;
    Interval(Coord bot, Coord top) : bot(bot), top(top) {}
    bool operator==(const Interval& i) const {
        return bot == i.bot && top == i.top;
    }
};

enum class EdgeType { Left, Top, Right, Bottom };

class Edge {
    Interval m_interval;
    Coord m_coord;
    EdgeType m_type;

   public:
    Edge() = delete;
    Edge(Interval i, Coord c, EdgeType t)
        : m_interval(i), m_coord(c), m_type(t) {}
    Interval interval() const { return m_interval; }
    Coord coord() const { return m_coord; }
    EdgeType type() const { return m_type; }
    bool operator<(const Edge& e) const {
        return m_coord < e.coord() ||
               (m_type != e.type() && m_type == EdgeType::Left);
    }  // y_interval yet to complete
};

class Stripe {
   public:
    Interval m_x_interval;
    Interval m_y_interval;
    std::set<Interval> m_x_union;
    Stripe(Interval x_ext, Interval y_ext)
        : m_x_interval(x_ext), m_y_interval(y_ext) {}
    bool operator==(const Stripe& s) const {
        return m_x_interval == s.m_x_interval &&
               m_y_interval == s.m_y_interval && m_x_union == s.m_x_union;
    }
};

class Rectangle {
    Coord m_xleft;
    Coord m_ytop;
    Coord m_xright;
    Coord m_ybot;

   public:
    Rectangle() = delete;
    Rectangle(Point ul, Point lr)
        : m_xleft(ul.x), m_ytop(ul.y), m_xright(lr.x), m_ybot(lr.y) {}
    Rectangle(Interval x_axis, Interval y_axis)
        : m_xleft(x_axis.bot),
          m_ytop(y_axis.top),
          m_xright(x_axis.top),
          m_ybot(y_axis.bot) {}
    Point upper_left() const { return {m_xleft, m_ytop}; }
    Point lower_right() const { return {m_xright, m_ybot}; }
    Interval x_interval() const { return {m_xleft, m_xright}; }
    Interval y_interval() const { return {m_ybot, m_ytop}; }
    std::array<Edge, 4> into_edges() const;
};

#endif
