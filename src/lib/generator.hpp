#ifndef DAA_GENERATOR
#define DAA_GENERATOR

#include <random>
#include <vector>

#include "common.hpp"

double const MIN_COORD = 0.0;
double const MAX_COORD = 100.0;

class SetGenerator {
   private:
    std::default_random_engine engine;
    std::uniform_real_distribution<double> distrib;

   public:
    SetGenerator(int seed = 42, const double min_coord = MIN_COORD,
                 const double max_coord = MAX_COORD) {
        engine.seed(seed);
        distrib = std::uniform_real_distribution<double>(min_coord, max_coord);
    }
    std::vector<Rectangle> int_rects(size_t n);
    std::vector<Rectangle> real_rects(size_t n);
};
#endif
