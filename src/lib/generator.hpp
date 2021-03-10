#include <random>

unsigned int const MIN_COORD = 0;
unsigned int const MAX_COORD = 100;

class SetGenerator {
   private:
    std::default_random_engine engine;

   public:
    SetGenerator(int seed) { engine.seed(seed); }
};