/*
 * @file .cpp
 * @decription Compute relative entropy (a.k.a. KL divergence) KL(p(x)||p(y)) of two discrete variables
 */

#include <iostream>
#include <cmath>
#include <array>
#include <cassert>

/*
 * @brief Calculate relative entropy of two integer vectors via KL(p(x)||p(y))
 * @param x array 
 * @param y array of similar length
 * @return relative entropy
 */
template <typename T, size_t size>
float relatEntropy(std::array<T, size> &x,
                   std::array<T, size> &y){
  assert(x.size() == y.size());
  int n = x.size();
  int minX = x[0];
  int minY = y[0];
  for(int i = 1; i<n; i++){
    minX=std::min(minX, x[i]);
    minY=std::min(minY, y[i]);
  }
  int l = std::min(minX,minY);
  float entropyXY;
  for (int i = 0; i < n; i++){
    x[i]=x[i]-l+1;
    y[i]=y[i]-l+1;
    entropyXY-=x[i]*(std::log2(y[i])-std::log2(x[i]));
  }
  return entropyXY;
}

int main(){
  std::cout << "Compute relative entropy: " << std::endl;
  std::array<int, 3> x {1, 2, 3};
  std::array<int, 3> y {2, 3, 4};
  std::cout << relatEntropy(x, y) << std::endl;
}
