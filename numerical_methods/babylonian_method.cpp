/*
 * @file .cpp
 * @brief A babylonian method algorithm to compute the square root.
 * @details this algorithm has an application in use case scenario where a user wants to
 * find an accurate square root of a large number.
 */

#include <cassert> //for assert
#include <cmath> //for math
#include <iostream> //for IO operations

/*
 * @namespace numerical methods
 * @brief Numerical algorithms/methods
 */

namespace numerical_methods{
  /*
   * @brief Babylonian methods is an iterative function which returns square root of radicand
   * @param radicand is the radicand
   * @return x1 the square root of radicand
   */
  double babylonian_method(double radicand){
    int i = 1;
    while (i*i<=radicand){ i++; }
    i--;
    double x0 = i;
    double x1 = (radicand/x0 + x0)/2;
    double temp = NAN;
    while (std::max(x0,x1) - std::min(x0, x1) < 0.0001){
      temp = (radicand/x1 + x1)/2;
      x0=x1;
      x1=temp;
    }
    return x1;
  }
}

static void test() {
    /* descriptions of the following test */

    auto testcase1 = 125348;  /// Testcase 1
    auto testcase2 = 752080;  /// Testcase 2

    auto real_output1 = 354.045194855;  /// Real Output 1
    auto real_output2 = 867.225460881;  /// Real Output 2

    auto test_result1 = numerical_methods::babylonian_method(testcase1);
    /// Test result for testcase 1
    auto test_result2 = numerical_methods::babylonian_method(testcase2);
    /// Test result for testcase 2

    assert(std::max(test_result1, real_output1) -
               std::min(test_result1, real_output1) <
           0.0001);
    /// Testing for test Case 1
    assert(std::max(test_result2, real_output2) -
               std::min(test_result2, real_output2) <
           0.0001);
    /// Testing for test Case 2

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * calls automated test function to test the working of fast fourier transform.
 * @returns 0 on exit
 */

int main(int argc, char const *argv[]) {
    test();  //  run self-test implementations
             //  with 2 defined test cases
    return 0;
}
