/*
 * @file
 * A simple program to check if the given number if prime or not
 *
 * @brief
 * Reduce all possibilities of a number which cannot be prime.
 * Eg. No even number, except 2 can be a prime number, hence we will increment loop with i+6
 * jumping and checking for i or i+2 to be a factor of the number; if it's a factor then
 * we wil return false otherwise true after the loop terminates at the terminating condition (i*i<=num)
 */

#include <cassert>
#include <iostream>

/*
 * Function to check if the given number is prime or not.
 * @param num number to be checked
 * @return if number is prime, it returns @ true, else it returns @ false
 */
template <typename T>
bool is_prime(T num) {
  bool result = true;
  if (num <= 1) {
    return false;
  } else if (num == 2 || num == 3) {
    return true;
  } else if ((num % 2) == 0 || num % 3 == 0) {
    return false;
  } else {
    for (T i = 5; (i*i) <= (num); i = (i+6)) {
      if ((num % i) == 0 || (num % (i + 2) == 0)) {
        result = false;
        break;
      }
    }
  }
  return (result);
}

int main() {
  assert(is_prime(50) == false);
  assert(is_prime(115249) == true);
  int num = 0;
  std::cout << "Enter a number to check if prime" << std::endl;
  std::cin >> num;
  bool result = is_prime(num);
  if (result) {
    std::cout << num << "is a prime number" << std::endl;
  } else {
    std::cout << num << " is not a prime number" << std::endl;
  }
  return 0;
}
