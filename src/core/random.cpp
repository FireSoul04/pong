#include "random.hpp"

uint64_t Random::m_Seed = static_cast<uint64_t>(system_clock::now().time_since_epoch().count());
std::default_random_engine Random::m_Generator(m_Seed);

Random::Random() {
}

const int Random::generate(const int a, const int b) {
    std::uniform_int_distribution<int> range(a, b);
    return range(m_Generator);
}

const double Random::generateDouble(const double a, const double b) {
    std::uniform_real_distribution<double> range(a, b);
    return range(m_Generator);
}