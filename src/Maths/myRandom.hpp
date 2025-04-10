#pragma once

#include <random>

class RandomDevice {
private:
  std::mt19937 generator;

public:
  void init(int seed) { generator.seed(seed); }

  double randomDouble() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
  }

  int randomIntUniforme(int min, int max) {
    ;
    return min + (int)(randomDouble() * (max - min + 1));
  }

  int randomIntBinomial(int trials, double probability) {
    int count = 0;
    for (int i = 0; i < trials; ++i) {
      if (randomDouble() < probability) {
        ++count;
      }
    }
    return count;
  }
};