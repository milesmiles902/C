/*
 * @file .cpp
 * @brief Faster computation for a^b
 * @description Program that computes a^b in O(logN) time.
 * The formula is:
 * 1. If b is even;
 *    a^b = a^{b/2} (dot) a^{b/2} = a^{b/2}^2
 * 2. If b is odd 
 *    a^{b-1 / 2} (dot) a^{b-1 / 2} (dot) a = a^{b-1 / 2}^2 (dot) a
 */

#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdlib>
#include <ctime>
#include <iostream>

template <typename T>
double fast_power_recursive(T a, T b) {
  if(b<0)
    return 1.0 / fast_power_recursive(a, -b);
  if (b==0)
    return 1;
  T bottom = fast_power_recursive(a, b >> 1);
  double result;
  if ((b & 1) == 0)
    result = bottom * bottom;
  else 
    result = bottom * bottom * a;
  return result;
}

template <typename T>
double fast_power_linear(T a, T b){
  if (b<0)
    return 1.0 / fast_power_linear(a, -b);
  double result = 1;
  while(b) {
    if (b&1)
      result = result*a;
    a = a*a;
    b = b >> 1;
  }
  return result;
}
