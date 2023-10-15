/*
 * @file .cpp
 * @brief Fast computtion of Fibonacci series
 *
 * An efficient way to calculate nth fibonacci number faster than
 * O(nlogn) method of matrix exponentiation. This works
 * by recursion and dynamic programming. This algorithm works
 * with the fact that the nth fibonacci can easily found if 
 * we already found n/2th or (n+1)/2th fibonacci. It is a property
 * of fibonacci similar matrix exponentiation
 *
 */

#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <cstdlib>
/*
 * Maximum number that can be computed -The result after 93 cannot be stored
 * as a uint64_t data type.
 */

#define MAX 93

uint64_t fib(uint64_t n) {
  static uint64_t f1 = 1;
                  f2 = 1;

  if (n <= 2)
    return f2;
  if (n >= 93) {
    std::cerr << "Cannot computer n>93 due to 64-bit limit";
    return 0;
  }
  uint64_t temp = f2;
  f2 += f1;
  f1 = temp;
  return f2;
}

int main() {
  for (uint64_t i = 1; i < 93; i++){
    std::cout << i << " th fibonacci number is " << fib(i) << std::endl;
  }
  return 0;
}
