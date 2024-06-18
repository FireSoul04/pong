#pragma once

#include <random>
#include <chrono>
#include <cstdint>

using namespace std::chrono;

class Random {
public:
    static const int generate(const int a, const int b);
    static const double generateDouble(const double a, const double b);

private:
    Random();

private:
    static uint64_t                               m_Seed;
    static std::default_random_engine             m_Generator;
};