/*
 * @file .cpp
 * @brief Compute [double factorial]
 *
 * @description Double factorial of a non-negative integer 'n', is defined as the product of all the integers from 1  * to n that have the same parity (odd or even) as n. A semifactorial n!!
 */

#include <cassert>
#include <iostream>

/*
 * Compute double factorial using iterative method
 */
uint64_t double_factorial_iterative(uint64_t n) {
  uint64_t res = 1;
  for (uint64_t i = n;; i-=2) {
    if (i==0 || i == 1)
      return res;
    res *= i;
  }
  return res;
}

uint64_t double_factorial_recursive(uint64_t n) {
  if (n<=1)
    return 1;
  return n * double_factorial_recursive(n-2);
}

void test(uint64_t n, uint64_t expected) {
  assert(double_factorial_iterative(n) == expected);
  assert(double_factorial_recursive(n) == expected);
}

void tests() {
  std::cout << "Test 1:\t n=5\t...";
  test(5,15);
  std::cout << "passed\n";
}

int main() {
  tests();
  return 0;
}
