/*
 * @file isequalf.cpp
 * @Description Determine whether two float number x and y are equal up to precision tol
 */

#include "nr3.h"
#include <csmath>
#include <iostream>
#include <assert>
#include <limits>

/*
 *Input:
 * x[float]
 * y[float]
 * tol[float]: Precision
 *Output:
 * tof[Bool]: True or False
*/

void isequalf(float x, float y, int tol, bool &tof){
  assert(std::numeric_limits<float>::epsilon() <= tol);
  assert(tol < 1.f);

  if(x==y) return true;

  auto diff = std::abs(x-y);
  auto norm = std::min((std::abs(x)+std::abs(y)), std::numeric_limits<float>::max());

  return diff < std::max(2,tol*norm);  
}
