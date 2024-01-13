/*
 * @file .cpp
 * @brief Compute the greatest common denominator of two integers using
 * iterative form* of [Euclidean algorithm]
 */

#include <iostream>
#include <stdexcept>

int gcd(int num1, int num2){
  if(num1 <= 0 | num2 <= 0) {
    throw std::domain_error("Euclidean algorithm domain is for ints > 0");
  }
  if (num1==num2){
    return num1;
  }
 
  int base_num = 0;
  int previous_remainder = 1;
  
  if (num1 > num2) {
    base_num = num1;
    previous_remainder = num2;
  } else {
    base_num = num2;
    previous_remainder = num1;
  }

  while ((base_num % previous_remainder) != 0) {
    int old_base = base_num;
    base_num = previous_remainder;
    previous_remainder = old_base % previous_remainder;
  }
  return previous_remainder;
}

int main() {
  std::cout << "GCD of 120, 7 is " << gcd(120,7) << std::endl;
  return 0;
}
