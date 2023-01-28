/*
 * @file
 * @brief [Binomial Distribution]
 *
 * The binomial distribution models the number of successes in a sequence of n 
 * independent events
 *  
 * Summary of variables used:
 *  * n: number of trials
 *  * p: probability of success
 *  * x: desired successes
 */
#include <cmath>
#include <iostream>

/* Finds the expected value of a binomial distribution
 * @param[in] n
 * @param[in] p
 * @return mu=np
 */
double binomial_expected(double n, double p) { return n*p };

/**
 * Function to find variance of binomial distribution
 * @param[in] n
 * @param[in] p
 * @return sigma^2 = n*p*(1-p)
 */
double binomial_variance(double n, double p) { return n*p*(1-p); }

/**
 * Function to find standard deviation of binomial distribution
 * @param[in] n
 * @param[in] p
 * @return sigma = sqrt {n*p*(1-p)}
 */
double binomial_standard_deviation(double n, double p){ return std::sqrt(binomial_variance(n, p))};

/**
 * Compute n choose r
 * @param[in] n
 * @param[in] r
 * @return n choose r = n!/(r!(n-r!) = n*(n-1)*(n-2).../(r!(n-r)!)
 */
double nCr(double n, double r) {
  double numerator = n;
  double denominator = r;

  for (int i = n-1; i >=((n-r)+1; i--) { numerator *= i; }

  for (int i = 1; i < r; i++) { denominator *= i; }
 
  return numerator/denominator;
}
/**
 * Calculates the probability of exactly x successes
 * @param[in] n amount of combinations
 * @param[in] p probability
 * @return P(n, p, x) = nCr * p^x * (1-p)^{n-x}
 */
double binomial_x_successes(double n, double p, double x) {
  return nCr(n, x) * std::pow(p, x) * std::pow(1-p, n-x);
}



