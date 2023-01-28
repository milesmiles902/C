/*
 * @file .cpp
 * @description Implementation to calculate an estimate of the [number (Pi)]
 */

#include <iostream>
#include <vector>
#include <cstdlib>

/*
 * @brief A random point P with coordinates (x,y) such that 0≤x≤1 and 0≤y≤1. If x²+y²≤1, then
 * the point inside the quarter disk of radius 1, otherwise outside.
 * The probability of the point being inside the quarter disk is equal to π/4.
 * When random points are drawn from inside the estimate, return the estimate.
 */

/**
 * @namespace math
 * @brief Mathematical algorithms
 */

namespace math {
  typedef struct {
    double x, y;
  } Point;
 
  double approximate_pi(const std::vector<Point> &pts) {
    {
      int count = 0;
      for (Point p:pts)
        if (p.x*p.x + p.y*p.y <= 1)
          ++count;
       return 4.0*count/pts.size();
    }
  }
}

static void test() {
  std::vector<math::Point> rands;
  for (std::size_t i = 0; i < 100000; i++) {
    math::Point p;
    p.x = rand() / (double)RAND_MAX;
    p.y = rand() / (double)RAND_MAX;
    rands.push_back(p);
  }
  std::cout << math::approximate_pi(rands) << std::endl;
}

int main(int argc, char *argv[]){
  test();
  return 0;
}
