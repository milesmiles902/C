/*
 * @file .cpp
 * @brief C++ program to find factorial of a given number
 */
#include <iostream>

unsigned int factorial(unsigned int n){
  if (n == 0)
    return 1;
  return n*factorial(n-1);
}

int main(){
  int num = 5;
  std::cout << "Factorial of " << num << "is" << factorial(num) << std::endl;
  return 0;
}
