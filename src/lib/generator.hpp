#ifndef DAA_GENERATOR
#define DAA_GENERATOR

#include <random>
#include <vector>

#include "common.hpp"

const int32_t MIN_COORD = 0.0;
const int32_t MAX_COORD = 100.0;

class SetGenerator {
   private:
    std::default_random_engine engine;
    std::uniform_int_distribution<int32_t> distrib;

   public:
    SetGenerator(int seed = 42, const int32_t min_coord = MIN_COORD,
                 const int32_t max_coord = MAX_COORD) {
        engine.seed(seed);
        distrib = std::uniform_int_distribution<int32_t>(min_coord, max_coord);
    }
    std::vector<Rectangle> rects(size_t n);
};
#endif
