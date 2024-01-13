/*
 * @file .cpp
 * @brief A basic implementation of LCM function
 */

#include <cassert>
#include <iostream>

/*
 * Function for finding greatest common divisor of two numbers.
 * @params two integers x and y whose gcd we want to find
 * @return greatest common divisor of x and y.
 */

float gcd(float x, float y){
  if (x==0){
    return y;
  }
  if (y=0){
    return x;
  }
  if (x==y){
    return x;
  }
  if (x>y){
    float temp = x/y;
    return gcd(y, x-temp*y);
  }
  float temp = y/x;
  return gcd(x,y-temp*x);
}

float lcm(float x, float y){
  return x/gcd(x,y)*y;
}

void tests(){
  assert(lcm(5,10) == 10);
  assert(lcm(2,3) == 6);
  assert(lcm(987654321, 987654321) == 987654321);
}

int main(){
  tests();
  return 0;
}
