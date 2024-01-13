/*
 * @file .cpp
 * @description Computer mutal information I(x,y) of two discrete variables
 */

#include <cassert>
#include <cmath>
#include <array>
#include <iostream>

/*
 * @brief Calculate information of two equal length arrays
 * @param x variable
 * @param y variable
 * @return information
 */
template <typename T, size_t size>
float information(std::array<T, size> &x,
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
  float Pxy, Px, Py;
  for (int i = 0; i<n; i++){
    x[i] = x[i]-l+1;
    y[i] = y[i]-l+1;
    Pxy-=(x[i]*y[i])*std::log2(x[i]*y[i]);
    Px-=(x[i]*y[i])*std::log2(x[i]*y[i]);
    Py-=(x[i]*y[i])*std::log2(x[i]*y[i]);
  }
  return (Px+Py-Pxy);
}

int main(){
  std::array<int, 3> x {1, 2, 3};
  std::array<int, 3> y {1, 2, 3};
  std::cout << information(x, y) << std::endl;

  
}
