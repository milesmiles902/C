/*
 * @file .cpp
 *
 * @brief [Program to count digits]
 * @details A basic math program to find number of digits
 * E.g. K=floor(log10(N)+1)
 */

#include <cassert>
#include <iostream>
#include <cstdint>

/*
 * @brief The main function that checks the number of digits in a number
 * @param n the number to check digits
 * @return the digit count
 */

uint64_t finding_number_of_digits(uint64_t n){
  uint64_t count = 0;
  while (n!=0){
    n/=10;
    ++count;
  }
  return count;
}

int main(){
  assert(finding_number_of_digits(5492) == 4);
  return 0;
}
