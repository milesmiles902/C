/*
 * @file log1mexp.cpp
 * @Description Accurately comput y=log(1-exp(x));
 * @Eqns #
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * x[d]: Input Data
 *Output:
 * y[d]: Output Data
*/

void log1mexp(VecDoub x, VecDoub &y){
  int i,j;
  VecDoub index(x.size());
  y=x;
  for(i=0;i<x.size();i++){
    if(x[i]<-log(2)){
      y[i]=log(1-exp(x[i]));
    }
  }
}
