/*
 * @file .cpp
 * @description Compute log pdf of Dirichlet distribution
 */
#include <cmath>
#include <iostream>
#include <array>

/*
 * @brief Compute log of Dirichlet distribution
 * @param x DxN data matrix
 * @param a DxK parameter of Dirichlet
 * @param y KxN probability density
 * @return log(Coefficient)+(a-1)*log(average)
 */

template <typename T, size_t size>
float logDirichlet(std::array<std::array<float, size>, size> &x,
                   std::array<std::array<T, size>, size> &a,
                   std::array<std::array<T, size>, size> &y){
  int sumX, sumA, sumG;
  int rows = (sizeof x)/(sizeof x[0]);
  int cols = sizeof x[0]/sizeof(int);
  for (int i = 0; i<rows; i++){
    for (int j = 0; j<cols; j++){
      sumX+=x[i][j];
      sumA+=a[i][j];
      sumG+=lgamma(a[i][j]);
    }
  }
  for (int i = 0; i<rows; i++){
    for (int j = 0; j<cols; j++){
      x[i][j]=x[i][j]/sumX;
    }
  }
  float c = lgamma(sumA)-sumG;
  float g;
  for (int i = 0; i<rows; i++){
    for (int j = 0; j<cols; j++){
      g = (a[i][j]-1)*std::log2(x[i][j]);
    }
  }
  return c+g;
}

int main(){
  std::cout << "Compute log pdf of Dirichlet distribution: " << std::endl;  
  std::array<std::array<float, 3>, 3> x { { {1.0, 2.0, 3.0}, 
                                          {4.0, 5.0, 6.0}, 
                                          {7.0, 8.0, 9.0} 
                                      } };
  std::array<std::array<int, 3>, 3> a { { {10, 11, 12}, 
                                          {13, 14, 15}, 
                                          {16, 17, 18}
                                      } };
  std::array<std::array<int, 3>, 3> y { { {1, 2, 3}, 
                                          {4, 5, 6}, 
                                          {7, 8, 9}
                                      } };
  std::cout << logDirichlet(x, a, y) << std::endl;
}
