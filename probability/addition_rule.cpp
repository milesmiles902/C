/**
 * @file
 * @brief Addition rule of probabilities
 */
#include <iostream>

/**
 * Calculates the probability of the independent events A or B for independent events
 * @param[in] A probability of event A
 * @param[in] B probability of event B
 * @param[in] B_given_A probability of event B condition A
 * @return probability of A and B
 */
double addition_rule_independent(double A, double B) {
  return (A+B) - (A * B);
}

/**
 * Calculatte the probabilitties of events A or B for dependent events
 * if B_given_A is unknown, then apply chainrule to find it.
 * @param[in] A probability of event A
 * @param[in] B probability of event B
 * @param[in] B_given_A probability of event B condition A
 * @return probability of A and B
 */
double addition_rule_dependent(double A, double B, double B_given_A) {
  return (A+B) - (A*B_given_A);
}

