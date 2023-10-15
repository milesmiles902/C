/**
 * @file .cpp
 * @brief Solve the equation f(x)=0 using [bisection method]
 *
 * Given two points a<0 and b>0, then (i+1)^th approximation is given by:
 * x_{i+1}=(a+b)/2
 *
 * For the next iteration, the interval is selected as: [a,x] if or x[x,b] if x<0. The process is
 * continued till a close enough approximation is achieved. 
 */

#include <cmath>
#include <iostream>
#include <limits>
#include <cstdlib>

#define EPSILON 1e-6 // std::numerical_limits<double>::epsilon() 
#define MAX_ITERATIONS 50000

/*
 * @brief define root f(x)
 * @param i power of root
 * @return i^3-4i-9
 */
static double eq(double i){
  return (std::pow(i,3) - (4*i)-9);
}

template <typename T>
int sgn(T val){
  return (T(0) < val) - (val< T(0));
}

int main() {
  double a = -1, b = 1, x, z;
  int i;

  for (int i =0; i<MAX_ITERATIONS;i++){
    z = eq(a);
    x = eq(b);
    if (sgn(z) == sgn(x)) {
      b++;
      a--;
    } else{
      break;
    }
  }
  std::cout << "\nFirst initial: " << a;
    std::cout << "\nSecond initial: " << b;

    // start iterations
    for (i = 0; i < MAX_ITERATIONS; i++) {
        x = (a + b) / 2;
        z = eq(x);
        std::cout << "\n\nz: " << z << "\t[" << a << " , " << b
                  << " | Bisect: " << x << "]";

        if (z < 0) {
            a = x;
        } else {
            b = x;
        }

        if (std::abs(z) < EPSILON)  // stoping criteria
            break;
    }

    std::cout << "\n\nRoot: " << x << "\t\tSteps: " << i << std::endl;
    return 0;
}
