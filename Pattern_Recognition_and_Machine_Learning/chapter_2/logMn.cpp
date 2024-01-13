/*
 * @file .cpp
 * @brief Logarithm probability Distribution of a Multinomial Distribution
 */

#include <cmath>
#include <iostream>
#include "nr3.h"

void logMn(VecDoub x, VecDoub p, Doub &z){
  int i,j,sumx, sumgam, dotxp;
  for(i=0;i<x.size();i++){
    sumx+=x[i];
    sumgam+=lgamma(x[i]+1);
    dotxp+=x[i]*log(p[i]);
  }
  z=sumx+sumgam+dotxp;
}


int main(){
  VecDoub x(25), p(25);
  Doub z;
  for (int i=0;i<x.size();i++){
    x[i]=rand();
    p[i]=rand();
  }
  logMn(x,p,z);
  std::cout << z << std::endl;
}
