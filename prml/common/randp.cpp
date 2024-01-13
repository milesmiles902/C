/*
 * @file randp.cpp
 * @Description Sample a integer [1:k] with given probability p
 */

#include "nr3.h"
#include <csmath>
#include <iostream>
#include <random>

/*
 *Input:
 * p(n): Input Data
 *Output:
 * i: Sample
*/

void randp(VecDoub p, int &i){
  return i=p[rand()%p.size()];
}

