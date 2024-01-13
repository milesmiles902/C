/**
 * @file .cpp
 * @brief Compute the greatest common denominator of two integers [recursive]
 */

#include <iostream>

int gcd(int num1, int num2){
  if (num1 <= 0 | num2 <= 0){
    throw std::domain_error("Euclidean algorithm domain is for ints > 0");
  }
  if (num1 == num2){
    return num1;
  }
  if (num1 == 0)
    return num2;
  if (num2 == 0)
    return num1;

  if (num1 == num2)
    return num1;
 
  if (num1 > num2)
    return gcd(num1-num2, num2);
  return gcd(num1, num2-num1);
}

int main(){
  std::cout << "gcd of 312,221 is " << (gcd(312,221)) << std::endl;
}
