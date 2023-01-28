/*
 * @file .cpp
 * @brief Program to calculate [Binomial coefficients]
 */

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>

/*
 * @namespace math
 * @brief Mathematical Algorithms
 */
namespace math{
  /*
   * @namespace binomial
   * @brief Function for [Binomial Coefficients]
   */
  namespace binomial {
    /*
     * @brief Function to calculate binomial coefficients
     * @param n first value
     * @param k second value
     * @return binomial coefficient for n and k
     */
    size_t calculate(int32_t n, int32_t k) {
      //basic cases
      if (k > (n / 2))
        k = n - k;
      if (k == 1)
        return n;
      if (k == 0)
        return 1;
      size_t result = 1;
      for (int32_t i = 1; i <= k; ++i) {
        result *= n-k+i;
        result /= i;
      }
      return result;
    }
  }
}

static void tests() {
  assert(math::binomial::calculate(1, 1) == 1);
}

int main(int argc, const char* argv[]) {
  tests();
  if (argc < 3) {
    std::cout << "Usage ./binomial_calculate {n} {k}" << std::endl;
    return 0;
  }
  int32_t n = atoi(argv[1]);
  int32_t k = atoi(argv[2]);
  std::cout << math::binomial::calculate(n, k) << std::endl;
  return 0;
}
