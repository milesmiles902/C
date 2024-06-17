/*
 * @brief Conditional Entropy
 * @description A discrete function for computing conditional entropy
 * @param x integer space
 * @param y integer space
 * @return z conditional integer space
 */
#include <cassert>
#include <iostream>
#include <array>
#include <cmath>

template <typename T, size_t size>
float condEntropy(std::array<T, size> &x,
                                std::array<T, size> &y){
  assert(x.size() == y.size());
  int n = x.size();
  int minX = x[0];
  int minY = y[0];
  for (int i=1; i < n; i++){
    minX = std::min(minX, x[i]);
    minY = std::min(minY, y[i]);
  }
  int l = std::min(minX, minY);
  float entropyXY, entropyY;
  for (int i=0; i<n; i++) {
    x[i] = x[i]-l+1;
    y[i] = y[i]-l+1;
    entropyXY -= x[i]*y[i]*std::log2(x[i]*y[i]);
    entropyY -= y[i]*std::log2(y[i]);
  }
  return (entropyXY-entropyY);
}

int main(){
  std::cout << "Check correctness with equal arrays: " << std::endl;
  std::array<int, 3> x {1,2,3};
  std::array<int, 3> y {1,2,3};
  std::cout << condEntropy(x, y) << std::endl;

  std::cout << "Check correctness with unequal arrays: " << std::endl;
  std::array<int, 3> a {1, 2, 3};
  std::array<int, 3> b {2, 3, 4};
  std::cout << condEntropy(a, b) << std::endl;
} 
