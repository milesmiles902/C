/**
 * @file .cpp
 * @brief Runge Kutta fourth order
 *
 * @details It solves the unknown value of y for a given value of x only first order differential equations
 * can be solved with this method
 * @example it solves dy/dx = (x-y)/2
 * given x for initial conditions
 */
#include <cassert>
#include <iostream>
#include <vector>

/*
 * @brief The change() function is used to return the updated iterative value corresponding to the given 
 * function.
 * @param x is the value corresponding to the x coordinate
 * @param y is the value corresponding to the y coordinate
 * @returns the computed function value at that call
 */
static double change(double x, double y) {return ((x-y)/2.0);}

/*
 * @namespace numerical methods
 * @brief Numerical Methods
 */
namespace numerical_methods{
  namespace runge_kutta{
    /*
     * @brief The Runge Kutta method finds the value of integration of a function in the given limits.
     * The lower limit of integration as the initial value and the upper limit is the given x.
     * @param init_x is the value of the initial x and is updated after each call
     * @param init_y is the value of the initial y and is updated after each call
     * @param x is the current interation at whic the function needs to be evaluated
     * @param h is the step value
     * @returns the value of y at the required value of x from the initial conditions
     */
    double rungeKutta(double init_x, const double &init_y, const double &x, const double &h){
      /* Count number of iterations
       * using step size or step height h
       *
       * n calculates the number of iterations
       * k1, k2, k3, k4 are the Runge Kutta variables
       * used for calculation of y at the iteration
       */
       auto n = static_cast<uint64_t>((x-init_x)/h);
       std::vector<double> k(4, 0.0);
     
       double y = init_y;
       for (int i = 1; i <= n; ++i) {
         k[0] = h*change(init_x, y);
         k[1] = h*change(init_x + 0.5 * h, y+0.5*k[0]);
         k[2] = h*change(init_x + 0.5 * h, y+0.5*k[1]);
         k[3] = h*change(init_x + h, y+k[2]);  
         y += (1.0/6.0) * (k[0] +2*k[1]+2*k[2]+k[3]);
         init_x +=h;
      }
      return y;
    }
  }
}

static void test() {
    std::cout << "The Runge Kutta function will be tested on the basis of "
                 "precomputed values\n";

    std::cout << "Test 1...."
              << "\n";
    double valfirst = numerical_methods::runge_kutta::rungeKutta(
        2, 3, 4, 0.2);  // Tests the function with pre calculated values
    assert(valfirst == 3.10363932323749570);
    std::cout << "Passed Test 1\n";

    std::cout << "Test 2...."
              << "\n";
    double valsec = numerical_methods::runge_kutta::rungeKutta(
        1, 2, 5, 0.1);  // The value of step changed
    assert(valsec == 3.40600589380261409);
    std::cout << "Passed Test 2\n";

    std::cout << "Test 3...."
              << "\n";
    double valthird = numerical_methods::runge_kutta::rungeKutta(
        -1, 3, 4, 0.1);  // Tested with negative value
    assert(valthird == 2.49251005860244268);
    std::cout << "Passed Test 3\n";
}

/**
 *  * @brief Main function
 *   * @returns 0 on exit
 *    */
int main() {
    test();  // Execute the tests
    return 0;
}
