#pragma once

#include <cstddef>
#include <random>

auto getGenerator(std::size_t seed=123){
   static std::random_device rdev;
   static std::mt19937_64 gen(rdev());
   gen.seed(seed);
   return gen;
}

