/**
 * @file
 * @brief [Bayes' theorem]
 *
 * Bayes' theorem allows one to find p(A|B) given p(B|A) or
 * p(B|A) given p(A|B) and p(A) and p(B)
 * Note that p(A|B) is read 'The probability of A given the event of B has occured'
 */
#include <iostream>

 /*
 * Function to return p(A|B)
 * @param[in] BgivenA prior probability
 * @param[in] A liklihood probability
 * @param[in] B normalization probability
 * @return AgivenB posterior probability
 */
double bayes_AgivenB(double BgivenA, double A, double B) { return (BgivenA*A)/B; };

 /*
 * Function to retturn p(B|A)
 * @param[in] AgivenB prior probability
 * @param[in] A liklihood probability
 * @param[in] B normalization probability
 * @return BgivenA posterior probability
 */
double bayes_BgivenA(double AgivenB, double A, double B) { return (AgivenB*B)/A; };

