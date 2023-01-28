/*
 * @file
 * @brief [Poisson Statistics]
 *
 * @function A Poisson distribution counts how many events
 * occur over a set of time interval
 */

#include <cmath>
#include <iostream>

/**
 * @brief Events per time expected
 * @param event amounts
 * @param timeframe duraction
 * @return events per time
 */
double poisson_rate(double events, double timeframe) {
  return events/timeframe;
}

/* @brief Amount expected from Poisson
 * @param rate
 * @param time
 * @return amount
 */
double poisson_expected(double rate, double time) { return rate*time; }

/* 
 * @brief Determine factorial of double
 * @param number
 * @return factorial of a number
 */
double fact(double x) {
  double x_fact = x;
  for (int i = x - 1; i > 0; i--) {
    x_fact *= i;
  }
  if (x_fact <= 0) {
    x_fact = 1;
  }
  return x_fact;
}

/**
 * @brief Find probability of x-successes in a Poisson distribution
 * @param expected
 * @param amount
 * @return probability
 */
double poisson_x_successes(double expected, double x) {
  return (std::pow(expected, x) * std::exp(-expected))/ fact(x);
}

/**
 * @brief Probability of a success in range for Poisson distribution (inclusive, inclusive)
 * @param expected amount
 * @param lower bound
 * @param upper bound
 * @return probability
 */
double poisson_range_successes(double expected, double lower, double upper) {
  double probability = 0;
  for (int i = lower; i <= upper; i++) {
    probability += poisson_x_successes(expected, i);
  }
  return probability;
}

/**
 * @Main Function
 */
int main() {
  double rate, expected;
  rate = poisson_rate(3, 1);
  std::cout << "Poisson rate : " << rate << std::endl;
  
  expected = poisson_expected(rate, 2);
  std::cout << "Poisson expected : " << expected << std::endl;

  std::cout << "Poisson 0 successes : " << poisson_x_successes(expected, 0) << std::endl;
  std::cout << "Poisson 0-8 success : " << poisson_range_successes(expected, 0, 8) << std::endl;
  return 0;
}
