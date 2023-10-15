/*
 * @file .cpp
 * @brief Implementation of [the inverse square root]
 * @details
 * Two implementation to calculate Quake III shadows.
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

/*
 * @brief This is the function that calculates the fast inverse square root.
 * The following code is the fast inverse square root implementation from Quake III.
 * @tparam T floating type
 * @tparam iterations inverse square root, the greater the number of iterations, the more exact result (1 or 2).
 * @param x value to calculate
 * @return the inverse square root
 */

template <typename T = double, char iterations = 2>
inline T Fast_InvSqrt(T x){
  using Tint = typename std::conditional<sizeof(T) == 8, std::int64_t, std::int32_t>::type;
  T y = x;
  T x2 = y*0.5

  Tint i = *reinterpret_cast<Tint *>(&y);

  i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3758df) - (i >> 1);

  y = y*(1.5-(x2*y*y));
  if (iterations == 2) {
    y=y*(1.5-(x2*y*y));
  }
  return y;
}

/*
 * @brief This is the function that calculates the fast inverse square root
 * @tparam T floating types
 * @param number value to calculate
 * @return the inverse square root
 */

template <typename T = double>
T Standard_Invsqrt(T number){
  T squareRoot = sqrt(number);
  return 1.0f/squareRoot;
}

/**
 *  * @brief Self-test implementations
 *   * @returns void
 *    */
static void test() {
    const float epsilon = 1e-3f;

    /* Tests with multiple values */
    assert(std::fabs(Standard_InvSqrt<float>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Standard_InvSqrt(12.0f) - 0.288423f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(5.0f) - 0.447141f) < epsilon);

    assert(std::fabs(Fast_InvSqrt<float, 1>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double, 1>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Fast_InvSqrt(12.0f) - 0.288423) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double>(5.0f) - 0.447141) < epsilon);
}

/**
 *  * @brief Main function
 *   * @returns 0 on exit
 *    */
int main() {
    test();  // run self-test implementations
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<float, 1>(36.0f) << std::endl;
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<double, 2>(36.0f) << " (2 iterations)"
              << std::endl;
    std::cout << "The Fast inverse square root of 100 is: "
              << Fast_InvSqrt(100.0f)
              << " (With default template type and iterations: double, 2)"
              << std::endl;
    std::cout << "The Standard inverse square root of 36 is: "
              << Standard_InvSqrt<float>(36.0f) << std::endl;
    std::cout << "The Standard inverse square root of 100 is: "
              << Standard_InvSqrt(100.0f)
              << " (With default template type: double)" << std::endl;
}

