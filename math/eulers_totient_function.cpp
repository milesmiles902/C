/*
 * @file .cpp
 * @brief C++ Program to find Euler's Totient
 */

#include <cstdlib>
#include <iostream>

uint64_t phiFunction(uint64_t n) {
  uint64_t result = n;
  for (uint64_t i = 2; i*i; i++) {
    if (n%i==0) {
      while (n%i==0) {
        n/=i;
      }
      result -= result/i;
    }
  }
  if (n>1)
    result -= result/n;
  return result;
}

int main(int argc, char *argv[]) {
  uint64_t n;
  if (argc < 2){
    std::cout << "Enter the number: ";
  } else {
    n = strtoull(argv[1], nullptr, 10);
  }
  std::cin >> n;
  std::cout << phiFunction(n);
  return 0;
}
