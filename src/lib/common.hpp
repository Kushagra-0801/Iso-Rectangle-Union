#ifndef DAA_COMMON
#define DAA_COMMON

#include <array>
#include <string>
#include <vector>

/**
 * Coord is the datatype used in the coordinate system.
 *
 * This is used so that the datatype used to represent a point can be changed
 * with minimal pain.
 */
typedef int32_t Coord;

/**
 * 2-D point class.
 *
 * Default contructor has been deleted. Both x and y coordinates must be given
 * to initialise the point.
 */
class Point {
   public:
    Coord x; /**< x coordinate of the Point */
    Coord y; /**< y coordinate of the Point */
    Point() = delete;
    Point(Coord x, Coord y) : x(x), y(y) {} /**< Constructor for Point class */
};

/**
 * A Range of Points.
 *
 * Has a bot and top member.
 */
class Interval {
   public:
    Coord bot; /**< Bottom bound for the Interval */
    Coord top; /**< Top bound for the Interval */
    Interval() = delete;
    /**
     * Constructor for Interval Class
     */
    Interval(Coord bot, Coord top) : bot(bot), top(top) {}
    /**
     * Equality compare Interval
     */
    bool operator==(const Interval& i) const {
        return bot == i.bot && top == i.top;
    }
    /**
     * Order 2 intervals based on bottom bound then top bound.
     */
    bool operator<(const Interval& i) const {
        return bot < i.bot || (bot == i.bot && top < i.top);
    }
    /**
     * Find if this interval is a subset of the given interval.
     */
    bool is_subset_of(const Interval&) const;
};

/**
 * Marker for edge as being the Left, Top, Right, Bottom edge of its rectangle.
 */
enum class EdgeType { Left, Top, Right, Bottom };

/**
 * Denotes an edge.
 *
 * The type marks the edge as being left, right, etc.
 * Since the edges are axis aligned, one coordinate is same for both end
 * points and in stored in coord. The interval gives the range that the
 * other coordinate spans.
 */
class Edge {
    Interval m_interval;
    Coord m_coord;
    EdgeType m_type;

   public:
    /**
     * Deleted Constructor
     */
    Edge() = delete;
    /**
     * Constructor
     */
    Edge(Interval i, Coord c, EdgeType t)
        : m_interval(i), m_coord(c), m_type(t) {}
    /**
     * Getter
     */
    Interval interval() const { return m_interval; }
    /**
     * Getter
     */
    Coord coord() const { return m_coord; }
    /**
     * Getter
     */
    EdgeType type() const { return m_type; }
    /**
     * Order 2 edges based on their coordinate, left edge smaller in case of
     * same coordinate.
     *
     * Note: Assumes that both edges have vertical orientation.
     */
    bool operator<(const Edge& e) const {
        return coord() < e.coord() ||
               (coord() == e.coord() && type() == EdgeType::Left);
    }
};

/**
 * Define a node of the Ctree as being a left edge node, right node, or an
 * internal node.
 */
enum class Lru { Left, Right, Undef };

/**
 * A Binary search tree of edge points.
 */
class Ctree {
   public:
    Coord x;     /**< x-coordinate for the ctree */
    Lru side;    /**< Type of the node */
    Ctree* lson; /**< Left child of the tree */
    Ctree* rson; /**< Right child of the tree */

    /**
     * Constructor for the Ctree class
     */
    Ctree(Coord x, Lru side, Ctree* lson = nullptr, Ctree* rson = nullptr)
        : x(x), side(side), lson(lson), rson(rson) {}
};

/**
 * The whole meat of the algorithm.
 *
 * Stripes are a horizontal segment of the plane whose vertical bounds are
 * the either 2 edges or 1 edge and infinity. No horizontal edge falls
 * inbetween a stripe.
 *
 * Stripes are the core data structure which are used to calculate both the
 * measure and the contour.
 */
class Stripe {
   public:
    Interval m_x_interval; /**< x-interval of the stripe */
    Interval m_y_interval; /**< y-interval of the stripe */
    Ctree* tree;           /**< root of the BST Ctree in this stripe */
    Coord x_measure;       /**< sum of x-interval spans lying in this stripe */

    /**
     * Constructor from the x and y intervals
     */
    Stripe(Interval x_ext, Interval y_ext)
        : m_x_interval(x_ext),
          m_y_interval(y_ext),
          tree(nullptr),
          x_measure(0) {}
    /**
     * Compare 2 stripes as equal based on the equality of their y-intervals
     */
    bool operator==(const Stripe& s) const {
        return m_y_interval == s.m_y_interval;
    }
};

/**
 * Container class for a rectangle.
 */
class Rectangle {
    Coord m_xleft;  /**< left most x coordinate */
    Coord m_ytop;   /**< top most y coordinate */
    Coord m_xright; /**< right most x coordinate */
    Coord m_ybot;   /**< bottom most y coordinate */

   public:
    /**
     * Deleted default constructor.
     */
    Rectangle() = delete;
    /**
     * Constructor taking the diagonal vertices.
     *
     * @param ul Upper left point of the rectangle.
     * @param lr Lower right point of the rectangle.
     */
    Rectangle(Point ul, Point lr)
        : m_xleft(ul.x), m_ytop(ul.y), m_xright(lr.x), m_ybot(lr.y) {}
    /**
     * Contructor taking the span along both axes.
     *
     * @param x_axis Span of the rectangle along x-axis.
     * @param y_axis Span of the rectangle along y-axis.
     */
    Rectangle(Interval x_axis, Interval y_axis)
        : m_xleft(x_axis.bot),
          m_ytop(y_axis.top),
          m_xright(x_axis.top),
          m_ybot(y_axis.bot) {}
    /**
     * Return the upper left vertex.
     */
    Point upper_left() const { return {m_xleft, m_ytop}; }
    /**
     * Return the lower right vertex.
     */
    Point lower_right() const { return {m_xright, m_ybot}; }
    /**
     * Return the x-interval.
     */
    Interval x_interval() const { return {m_xleft, m_xright}; }
    /**
     * Return the y-interval.
     */
    Interval y_interval() const { return {m_ybot, m_ytop}; }
    /**
     * Get edges of the rectangle.
     *
     * @return An Array of size 4 containing the 4 edges of the rectangle.
     * The edges are in the order Left, Top, Right, Bottom.
     */
    std::array<Edge, 4> into_edges() const;
};

#endif
