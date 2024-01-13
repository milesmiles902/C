/*
 * @file .cpp
 * @brief Compute integral approximation of the function using [Riemann sum]
 */

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>

/*
 * @namespace math
 * @brief Mathematical Functions
 */

namespace math{
  /*
   * @brief Computes integral approx
   * @param lb
   * @param ub
   * @param func
   * @param delt
   * @return integral approximation of function from [lb, ub]
   */
   double integral_approx(double lb, double ub, const std::function<double(double)>& func, double delta = 0.0001){
      double result = 0;
      uint64_t numDeltas = static_cast<uint64_t>((ub-lb)/delta);
      for (int i=0;i<numDeltas;i++){
        double begin = lb + i*delta;
        double end = lb + (i+1)*delta;
        result += delta*(func(begin) + func(end))/2;
      }
      return result;
   }

   void test_eval(double approx, double expected, double threshold) {
    assert(approx >= expected * (1 - threshold));
    assert(approx <= expected * (1 + threshold));
}

/**
 * @brief Self-test implementations to
 * test the `integral_approx` function.
 *
 * @returns `void`
 */
}  // namespace math

static void test() {
    double test_1 = math::integral_approx(
        3.24, 7.56, [](const double x) { return log(x) + exp(x) + x; });
    std::cout << "Test Case 1" << std::endl;
    std::cout << "function: log(x) + e^x + x" << std::endl;
    std::cout << "range: [3.24, 7.56]" << std::endl;
    std::cout << "value: " << test_1 << std::endl;
    math::test_eval(test_1, 1924.80384023549, .001);
    std::cout << "Test 1 Passed!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_2 = math::integral_approx(0.023, 3.69, [](const double x) {
        return x * x + cos(x) + exp(x) + log(x) * log(x);
    });
    std::cout << "Test Case 2" << std::endl;
    std::cout << "function: x^2 + cos(x) + e^x + log^2(x)" << std::endl;
    std::cout << "range: [.023, 3.69]" << std::endl;
    std::cout << "value: " << test_2 << std::endl;
    math::test_eval(test_2, 58.71291345202729, .001);
    std::cout << "Test 2 Passed!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_3 = math::integral_approx(
        10.78, 24.899, [](const double x) { return x * x * x - x * x + 378; });
    std::cout << "Test Case 3" << std::endl;
    std::cout << "function: x^3 - x^2 + 378" << std::endl;
    std::cout << "range: [10.78, 24.899]" << std::endl;
    std::cout << "value: " << test_3 << std::endl;
    math::test_eval(test_3, 93320.65915078377, .001);
    std::cout << "Test 3 Passed!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_4 = math::integral_approx(
        .101, .505,
        [](const double x) { return cos(x) * tan(x) * x * x + exp(x); },
        .00001);
    std::cout << "Test Case 4" << std::endl;
    std::cout << "function: cos(x)*tan(x)*x^2 + e^x" << std::endl;
    std::cout << "range: [.101, .505]" << std::endl;
    std::cout << "value: " << test_4 << std::endl;
    math::test_eval(test_4, 0.566485986311631, .001);
    std::cout << "Test 4 Passed!" << std::endl;
    std::cout << "=====================" << std::endl;

    double test_5 = math::integral_approx(
        -1, 1, [](const double x) { return exp(-1 / (x * x)); });
    std::cout << "Test Case 5" << std::endl;
    std::cout << "function: e^(-1/x^2)" << std::endl;
    std::cout << "range: [-1, 1]" << std::endl;
    std::cout << "value: " << test_5 << std::endl;
    math::test_eval(test_5, 0.1781477117815607, .001);
    std::cout << "Test 5 Passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
