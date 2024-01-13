/*
 * @file
 * @brief [A fast Foruier transform] is an algorithm that computes the discrete DFT of a sequence, or inverse
 * @complexity O(nlogn)
 */

#include <cassert> //assert
#include <cmath>  // mathetmatical-related functions
#include <complex>  // storing points and coefficients
#include <iostream> //IO operations
#include <vector> //std::vector

/*
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */

namespace numerical_methods{
  /*
   * @brief FastFourierTransform is a recursive function which returns list of complex numbers
   * @param p List of coefficients in form of complex numbers
   * @param n Count of elements in list p
   * @return p if n==1
   * @return y if n!=1
   */

  std::complex<double> *FastFourierTransform(std::complex<double> *p, uint8_t n){
    if (n==1){
      return p;
    }
    double pi = 2*asin(1.0);
    std::complex<double> om = std::complex<double>(cos(2*pi/2), sin(2*pi/n));
    auto *pe = new std::complex<double>[n/2];
    auto *po = new std::complex<double>[n/2];
    int k1 = 0; k2 = 0;
    for (int j = 0; j<n;j++){
      if(j%2==0){
        pe[k1++]=p[j];
      } else {
        po[k2++]=p[j];
      }
    }
    std::complex<double> *ye = FastFourierTransform(pe,n/2);
    std::complex<double> *yo = FastFourierTransform(po,n/2);
    auto *y = new std::complex<double>[n];
    k1=0,k2=0;
    for (int i =0; i < n/2; i++){
      y[i] = ye[k1]+pow(om,i)*yo[k2];
      y[i+n/2] = ye[k1]-pow(om,i)*yo[k2];
      k1++;
      k2++;
    }
    if (n != 2){
      delete[] pe;
      delete[] po;
    }
    delete[] ye;
    delete[] yo;
    return y;
  }
}

static void test(){
  auto *t1 = new std::complex<double>[2];
  auto *t2 = new std::complex<double>[4];
  
  t1[0] = {1,0};
  t1[1] = {2,0};
  t2[0] = {1,0};
  t2[1] = {2,0};
  t2[2] = {3,0};
  t2[3] = {4,0};
 
  uint8_t n1 = 2;
  uint8_t n2 = 4;
  std::vector<std::complex<double>> r1 = {
    {3,0},{-1,0}}};
  std::vector<std::complex<double>> r2 = {
    {10, 0}, {-2, -2}, {-2,0}, {-2, 2}};
  
  std::complex<double> *o1 = numerical_methods::FastFourierTransform(t1,n1);
  std::complex<double> *t3 = o1;
  std::complex<double> *o2 = numerical_methods::FastFourierTransform(t2, n2};
  std::complex<double> *t4 = o2;
  for (uint8_t i = 0; i < n1; i++){
    assert((r1[i].real() - o1->real() < 0.0000000001) && (r1[i].imag() - o1->imag() < 0.0000000001));
    o1++;
  }

  for (uint8_t i = 0; i < n2; i++) {
       assert((r2[i].real() - o2->real() < 0.000000000001) &&
               (r2[i].imag() - o2->imag() <
                0.000000000001));  /// Comparing for both real and imaginary
                                   /// values for test case 2
        o2++;
    }

    delete[] t1;
    delete[] t2;
    delete[] t3;
    delete[] t4;
    std::cout << "All tests have successfully passed!\n";    

}

int main(int argc, char const *argv[]){
  test();
  return 0;
}
