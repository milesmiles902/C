/*
 * @file .cpp
 * @brief A C++ program to check whether a pair of numbers is [amicable pair]
 *
 * @description Amicable Pair are two positive integers such that the sum of the proper divisor
 * of each number is equal to the other number.
 */

#include <cassert>
#include <iostream>

/*
 * Function to calculate the sum of all the proper divsor of an integer
 * @param num First number
 * @return Sum of the proper divisor of the number
 */
int sum_of_divisor(int num) {
  int sum = 0;
  for (int div = 2; div*div <= num; ++div) {
    if (num % div == 0) {
      if (div == (num / div)) {
        sum += div;
      } else {
        sum += (div + (num / div));
      }
    }
  }
  return sum + 1;
}

bool are_amicable(int x, int y) {
  return (sum_of_divisor(x) == y) && (sum_of_divisor(y) == x);
}

void test() {
  assert(are_amicable(220,284) == true);
  assert(are_amicable(6368, 6232) == true);
  assert(are_amicable(458, 232) == false);
}

int main() {
  test();
  std::cout << "Assertion success." << std::endl;
  return 0;
}
