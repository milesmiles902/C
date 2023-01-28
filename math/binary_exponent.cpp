/*
 * @file .cpp
 * @brief C++ program to find binary exponent iteratively and recursively
 *
 * Calculate a^b in logb by converting b to a binary number. Binary exponentiation is also a known
 * as exponentiation by squaring.
 *
 * Example:
 * 10 in base 2 is 1010.
 * 2^{10_d} &=& 2^{1010_b} = 2^8 * 2*2;
 * 2^1 = 2
 * 2^2 = (2^1)^2 = 2^2 = 4
 * 2^4 = (2^2)^2 = 4^2 = 16
 * 2^8 = (2^2)^2 = 16^2 = 256
 */

#include <iostream>

// Recursive function to calculate exponent in log(n) using binary exponent
int binExpo(int a, int b) {
  if (b==0) {
    return 1;
  }
  int res = binExpo(a, b/2);
  if (b%2) {
    return res*res*a;
  } else {
    return res*res;
  }
}

int binExpo_alt(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b%2) {
      res = res * a;
    }
    a = a * a;
    b /= 2;
  }
  return res;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  if (a==0 && b==0) {
    std::cout << "Math error" << std::endl;
  } else if (b<0) {
    std::cout << "Exponent must be positive !!" << std::endl;
  } else { 
    int resRecurse = binExpo(a, b);
    std::cout << resRecurse << std::endl;
  }
}
