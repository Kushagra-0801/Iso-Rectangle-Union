#ifndef DAA_GENERATOR
#define DAA_GENERATOR

#include <random>
#include <vector>

#include "common.hpp"

const Coord MIN_COORD = 0;
const Coord MAX_COORD = 100;

class SetGenerator {
   private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int32_t> distrib;

   public:
    SetGenerator(int seed = 42, const Coord min_coord = MIN_COORD,
                 const Coord max_coord = MAX_COORD) {
        engine.seed(seed);
        distrib = std::uniform_int_distribution<Coord>(min_coord, max_coord);
    }
    std::vector<Rectangle> rects(size_t n);
};
#endif
