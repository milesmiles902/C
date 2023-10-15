/*
 * @file .cpp
 * @description Compute joint entropy of two discrete x and y vectors
 */

#include <cassert>
#include <cmath>
#include <array>
#include <iostream>

/*
 * @brief Function to calculate joint entropy
 * @param x vector 
 * @param y vector of same length
 * @return entropy
 */
template <typename T, size_t size>
float jointEntropy(std::array<T, size> &x,
                   std::array<T, size> &y) {
  assert(x.size() == y.size());
  int n = x.size();

  int minX = x[0];
  int minY = y[0];
  for (int i = 1; i < n; i++) {
    minX = std::min(minX, x[i]);
    minY = std::min(minY, y[i]);
  }
  int l = std::min(minX, minY);

  float entropy;  
  for (int i = 0; i < n; i++){
    x[i]=x[i]-l+1;
    y[i]=y[i]-l+1;
    entropy-=(x[i]*y[i])*std::log2(x[i]*y[i]);

  }
  return entropy; 
}

int main() {
  std::cout << "Joint entropy of two similar matrices" << std::endl;
  std::array<int, 3> x {1, 2, 3};
  std::array<int, 3> y {1, 2, 3};
  std::cout << jointEntropy(x, y) << std::endl;
 
  std::cout << "Joint entropy of two disimilar matrices" << std::endl;
  std::array<int, 3> a {1, 2, 3};
  std::array<int, 3> b {2, 3, 4};
  std::cout << jointEntropy(a, b) << std::endl;

}
