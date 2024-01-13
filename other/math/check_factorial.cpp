/*
 * @file .cpp
 * @brief A simple program to check if the given number is a factorial of some number or not
 */

#include <cassert>
#include <iostream>

/*
 * Function to check if the given number is factorial of some number or not.
 * @param n number to be checked
 * @return if number is a factorial, return true, else false.
 */

bool is_factorial(uint64_t n) {
  if (n <= 0) {
    return false;
  }
  for (uint32_t i = 1;;i++) {
    if (n % i != 0) {
      break;
    }
    n = n / i;
  }
  if (n == 1) {
    return true;
  } else {
    return false;
  }
}

void tests() {
  std::cout << "Test 1:\t n = 50\n";
  assert(is_factorial(50) == false);
  std::cout << "passed\n";
 
  std::cout << "Test 2:\t n = 720\n";
  assert(is_factorial(720) == true);
  std::cout << "passed\n";
}

int main() {
  tests();
  return 0;
}
