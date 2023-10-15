/*
 * @file .cpp
 * @brief Program to check if a number is an [Armstrong/Narcissitic number]
 * 
 * @details Armstrong number [Narcissistic number] is a number that is the sum of its 
 * own digits raise to the power of digits.
 */

#include <cassert>
#include <cmath>
#include <iostream>

/*
 * @brief Function to calculate the total number of digits in the number.
 * @param num Number
 * @return Total number of digits.
 */

int number_of_digits(int num) {
  int total_digits = 0;
  while (num > 0) {
    num = num / 10;
    ++total_digits;
  }
  return total_digits;
}

/*
 * @brief Function to check whether the number is armstrong number or not.
 * @param num Number
 * @return 'true' if the number is armstrong
 * @return 'false' if the number is not armstrong
 */

bool is_armstrong(int number) {
  // If the number is less than 0, then it is not a armstrong number.
  if (number < 0) {
    return false;
  }
  int sum = 0;
  int temp = number;
  int total_digits = number_of_digits(number);
  while (temp > 0) {
    int rem = temp % 10;
    sum = sum + std::pow(rem, total_digits);
    temp = temp / 10;
  }
  return number == sum;
}


