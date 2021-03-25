#ifndef DAA_GENERATOR
#define DAA_GENERATOR

#include <random>
#include <vector>

#include "common.hpp"

const Coord MIN_COORD = 0;   /**< Default Min Coordinate Bound for RNG*/
const Coord MAX_COORD = 100; /**< Default Max Coordinate Bound for RNG*/

/**
 * Generate random Rectangles
 */
class SetGenerator {
   private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int32_t> distrib;

   public:
    /**
     * Constructor
     *
     * @param seed The seed value for the generator. Default is 42.
     * @param min_coord The min coordinate value.
     * @param max_coord The max coordinate value.
     */
    SetGenerator(int seed = 42, const Coord min_coord = MIN_COORD,
                 const Coord max_coord = MAX_COORD) {
        engine.seed(seed);
        distrib = std::uniform_int_distribution<Coord>(min_coord, max_coord);
    }
    /**
     * Generate n random rectangles.
     *
     * @param n Number of rectangles wanted.
     *
     * @return Vector of n rectangles.
     */
    std::vector<Rectangle> rects(size_t n);
};
#endif
