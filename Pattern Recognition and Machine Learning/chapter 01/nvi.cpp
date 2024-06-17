/*
 * @file .cpp
 * @description Compute normalized variation information (1-I(x,y)/H(x,y)) of two discrete variables
 */

#include <array>
#include <cmath>
#include <cassert>
#include <iostream>

/*
 * @brief Function to normalize variational information
 * @param x vector
 * @param y vector of similar length
 * @return normalized entropy
 */

template <typename T, size_t size>
float nvi(std::array<T, size> &x,
          std::array<T, size> &y){
  assert(x.size() == y.size());
  int n = x.size();
  int minX = x[0];
  int minY = y[0];
  for (int i = 1; i < n; i++){
    minX = std::min(minX, x[i]);
    minY = std::min(minY, y[i]);
  }
  int l = std::min(minX, minY);
  float entropyX, entropyY, entropyXY;
  for(int i = 0; i<n; i++){
    x[i]=x[i]-l+1;
    y[i]=y[i]-l+1;
    entropyX-=x[i]*std::log2(x[i]);
    entropyY-=y[i]*std::log2(y[i]);
    entropyXY-=x[i]*y[i]*std::log2(x[i]*y[i]);
  }

  return (2-(entropyX+entropyY)/entropyXY);
}

int main() {
  std::array<int, 3> x {1, 2, 3};
  std::array<int, 3> y {1, 2, 3};
  std::cout << nvi(x, y) << std::endl;
}

